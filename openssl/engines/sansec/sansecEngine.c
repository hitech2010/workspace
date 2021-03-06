#include <string.h>
#include<openssl/engine.h>
#include<openssl/crypto.h>
#include<openssl/ossl_typ.h>
#include<openssl/evp.h>
#include<openssl/ecdsa.h>
#include<openssl/ec.h>
#include "swsds.h"
#include "sansecEngine.h"

SGD_HANDLE hDeviceHandle; /*global variable*/
SGD_HANDLE hSessionHandle;

/*
int sansec_init(ENGINE *e);
//sm3 functions
static int sansec_engine_sm3_init(EVP_MD_CTX *ctx);
static int sansec_engine_sm3_final(EVP_MD_CTX *ctx, unsigned char *md);
static int sansec_engine_sm3_update(EVP_MD_CTX *ctx, const void *data, size_t count);
//rand number functions
int get_random_bytes(unsigned char *buffer, int num);
*/

//rand
int get_random_bytes(unsigned char *buffer, int num){
    printf("sansec engine random length %d\n", num);
    memset(buffer, 1, num);
    return 99;
}
int sansec_random_status(void){
    return 1;
}
RAND_METHOD sansec_random_method = {
    NULL,
    get_random_bytes,
    NULL,
    NULL,
    NULL,
    sansec_random_status
};
//*****************************************************************************
//sm3**************************************************************************
static int sansec_engine_sm3_update(EVP_MD_CTX *ctx, const void *data, size_t count);

static int sansec_engine_sm3_init(EVP_MD_CTX *ctx){
    SGD_RV rv = SDF_OpenSession(hDeviceHandle, &hSessionHandle);
    if(rv != SDR_OK){
        printf("sm3_init, OpenSession failed, err [%08x]\n", rv);
        return 0;
    }
    rv = SDF_HashInit(hSessionHandle, SGD_SM3, NULL, NULL, 0);
    if(rv != SDR_OK){
        printf("sm3_init, HashInit failed, err[%08x]\n", rv);
        return 0;
    }
    EVP_MD_CTX_set_update_fn(ctx, sansec_engine_sm3_update); //this line is necessary, deep into. TODO
    printf("initialized SM3\n");
    return 1;
}
static int sansec_engine_sm3_update(EVP_MD_CTX *ctx, const void *data, size_t count){
    printf("sm3_update, data: %s, count: %d\n", data, count);
    SGD_RV rv = SDF_HashUpdate(hSessionHandle, data, count);
    if(rv != SDR_OK){
        printf("sm3_update, HashUpdate failed, err [%08x]\n", rv);
        return 0;
    }
    printf("SM3 update \n");
    return 1;
}
static int sansec_engine_sm3_final(EVP_MD_CTX *ctx, unsigned char *out){
    size_t outl;
    SGD_RV rv = SDF_HashFinal(hSessionHandle, out, &outl);
    if(rv != SDR_OK){
        printf("sm3_final, HashFinal failed, err [%08x]\n", rv);
        return 0;
    }
    printf("SM3 final\n");
    return 1;
}
static int sansec_engine_sm3_cleanup(EVP_MD_CTX *ctx){
    SGD_RV rv = SDF_CloseSession(hSessionHandle);
    if(rv != SDR_OK){
        printf("sm3_cleanup, CloseSession failed, err [%08x]\n", rv);
        return 0;
    }
    printf("sm3 cleanup\n");
    return 1;
}
#define SM3_BLOCKSIZE 64
#define SM3_DIGEST_SIZE 32
static EVP_MD *sansec_sm3(int nid){
    EVP_MD *md;
    if(((md = EVP_MD_meth_new(nid, NID_sm3WithRSAEncryption)) == NULL)
        || !EVP_MD_meth_set_init(md, sansec_engine_sm3_init)
        || !EVP_MD_meth_set_update(md, sansec_engine_sm3_update)
        || !EVP_MD_meth_set_final(md, sansec_engine_sm3_final)
        //|| !EVP_MD_meth_set_copy(md, sansec_engine_sm3_copy)
        || !EVP_MD_meth_set_cleanup(md, sansec_engine_sm3_cleanup)
        || !EVP_MD_meth_set_input_blocksize(md, SM3_BLOCKSIZE)
        || !EVP_MD_meth_set_result_size(md, SM3_DIGEST_SIZE))
            EVP_MD_meth_free(md);
    return md;
}
/*
static EVP_MD *sansec_engine_sm3_method = {
     NID_sm3,
     NID_sm3WithRSAEncryption,
     32,
     NULL,
     sansec_engine_sm3_init,
     sansec_engine_sm3_update,
     sansec_engine_sm3_final,
     NULL,
     NULL,
     //NULL,
     //NULL,
     //{NID_undef, NID_undef, 0, 0, 0},
     64,
     32,
     NULL
};
*/

//sm3 digest selector function
static int sansec_digest_ids[]={
    NID_sm3
};
static int sansec_digest_ids_num=sizeof(sansec_digest_ids)/
                                    sizeof(sansec_digest_ids[0]);
static int sansec_digests(ENGINE *e, const EVP_MD **digest, 
        const int **nids, int nid){
    if(!digest){
        printf("digest is NULL, setting nids to sansec_digest_ids, num: %d\n",
                                                     sansec_digest_ids_num);
        *nids = sansec_digest_ids;
        //return sansec_digest_ids_num;
        return 2;
    }
    switch(nid){
        case NID_sm3:
            printf("sansec_digest choose NID_sm3 %d\n", NID_sm3);
            *digest = sansec_sm3(nid);
            break;
        default:
            printf("sansec_digest choose %d, not known\n", nid);
            *digest = NULL;
            return 0;
    }
    return 1;
}
//*****************************************************************
//sm4 *************************************************************
SGD_HANDLE hKey;
static int sansec_cipher_init(EVP_CIPHER_CTX *ctx, const unsigned char *key,
    const unsigned char *iv, int enc)
{
    int rv = SDF_OpenSession(hDeviceHandle, &hSessionHandle);
    if(rv != SDR_OK){
        printf("OpenSession failed, err[0x%08x]\n", rv);
        return 0;
    }
    /*
    DEVICEINFO stDeviceInfo;
    rv = SDF_GetDeviceInfo(hSessionHandle, &stDeviceInfo);
    if (rv != SDR_OK){
        printf("GetDeviceInfo err[0x%08x]\n", rv);
    }else{
        printf("Producer Info: %s\n", stDeviceInfo.IssuerName);
    }
    */
    //printf("ImportKey....%d\n%s\n", strlen(key), key);
    rv = SDF_ImportKey(hSessionHandle, key, strlen(key), &hKey);
    if(rv != SDR_OK){
        printf("ImportKey err[0x%08x]\n", rv);
    }else{
        printf("ImportKey success. \n");
    }
    printf("sansec_cipher_init\n");
    return 1;
}
static int sansec_cipher_enc(EVP_CIPHER_CTX *ctx, unsigned char *out,
    const unsigned char *in, size_t inlen)
{
    int rv = 0, outl;
    if (0 == EVP_CIPHER_CTX_encrypting(ctx)){
        printf("sansec_cipher_enc decrypt...\n");
        rv = SDF_Decrypt(hSessionHandle, hKey, SGD_SMS4_ECB, NULL, in, inlen, out, &outl);
        if (rv != 0){
            printf("Decrypt err [0x%08x]\n", rv);
            return 0;
        }
    }else if(1 == EVP_CIPHER_CTX_encrypting(ctx)){
        printf("sansec_cipher_enc encrypt...\n");
        rv = SDF_Encrypt(hSessionHandle, hKey, SGD_SMS4_ECB, NULL, in, inlen, out, &outl);
        if(rv != 0){
            printf("Encrypt err [0x%08x]\n", rv);
            return 0;
        }
        //printf("Encrypted text: %s\n", out);
    }
    return 1;
}
static int sansec_cipher_cleanup(EVP_CIPHER_CTX *ctx){
    int rv = SDF_DestroyKey(hSessionHandle, hKey);
    if(rv != SDR_OK){
        printf("DestroyKey failed, err[0x%08x]\n", rv);
        return rv;
    }
    rv = SDF_CloseSession(hSessionHandle);
    if(rv != SDR_OK){
        printf("CloseSession failed, err[0x%08x]\n", rv);
        return rv;
    }
    printf("sansec_cipher_cleanup\n");
    return 1;
}
#define SM4_BLOCK_SIZE 16
#define SM4_KEYSIZE 16
#define SM4_IV_LEN 16
static const EVP_CIPHER *sansec_sm4(int nid){
    EVP_CIPHER *cipher;
    if (((cipher = EVP_CIPHER_meth_new(nid, SM4_BLOCK_SIZE, SM4_KEYSIZE)) == NULL)
        || !EVP_CIPHER_meth_set_iv_length(cipher, SM4_IV_LEN)
        || !EVP_CIPHER_meth_set_flags(cipher, EVP_CIPH_ECB_MODE | EVP_CIPH_FLAG_DEFAULT_ASN1)
        || !EVP_CIPHER_meth_set_init(cipher, sansec_cipher_init)
        || !EVP_CIPHER_meth_set_do_cipher(cipher, sansec_cipher_enc)
        || !EVP_CIPHER_meth_set_cleanup(cipher, sansec_cipher_cleanup))
            EVP_CIPHER_meth_free(cipher);
    
    return cipher;
}
/*
static const EVP_CIPHER *sansec_engine_sm4_method = {
    NID_sm4_ecb,
    16,
    16,
    0,
    8,
    sansec_cipher_init,
    sansec_cipher_enc,
    NULL,
    1,
    NULL,
    NULL,
    NULL,
    NULL
};
*/
static int sansec_cipher_nids[]={
    NID_sm4_ecb,
    NID_sm4_cbc,
    NID_sm4_cfb128,
    NID_sm4_ofb128,
    NID_sm4_ctr
};
static int sansec_cipher_nids_num = (sizeof(sansec_cipher_nids) / 
                                        sizeof(sansec_cipher_nids[0]));
static int sansec_ciphers(ENGINE *e, const EVP_CIPHER **cipher, const int **nids, int nid){
    if(!cipher){
        printf("cipher is NULL, setting nids to sansec_cipher_nids, num: %d\n", 
                                                     sansec_cipher_nids_num);
        *nids = sansec_cipher_nids;
        return  sansec_cipher_nids_num; 
    }
    switch(nid){
        case NID_sm4_ecb:
            printf("sansec_ciphers choose NID_sm4_ecb %d\n", NID_sm4_ecb);
            *cipher = sansec_sm4(nid);
            break;
        case NID_sm4_cbc:
            //*cipher = sansec_sm4_cbc();
            //break;
        default:
            printf("sansec_ciphers choose %d, Not known\n", nid);
            *cipher = NULL;
            return 0;
    }
    return 1;
}

//******************************************************************
//sm2 implementation************************************************
int sansec_engine_sm2_sign_setup(EC_KEY *key, BN_CTX *ctx_in, BIGNUM **kinvp,
        BIGNUM **rp){ return 1;}
static ECDSA_SIG *sansec_engine_sm2_sign(const unsigned char *dgst, int dgst_len,
            const BIGNUM *kinv, const BIGNUM *rp, EC_KEY *in_eckey){
    printf("sansec_engine_sm2_sign_sign...\n");
    return NULL;
}
static int sansec_engine_sm2_do_verify(const unsigned char *digest, int digest_len,
        const ECDSA_SIG *ecdsa_sig, EC_KEY *eckey){
    printf("sansec_engine_sm2_do_vefiry...\n");

    return 1;
}
/*
static ECDSA_METHOD *sansec_engine_sm2_method={
    "Sansec engine SM2 method",
    sansec_engine_sm2_sign,
    sansec_engine_sm2_sign_setup,
    sansec_engine_sm2_do_verify,
};
*/

//ENGINE init
int sansec_init(ENGINE *e){
    SGD_RV rv = SDF_OpenDevice(&hDeviceHandle);
    if(rv != SDR_OK){
        printf("OpenDevice err [0x%08x]\n", rv);
        return rv;
    }
    printf("sansec Engine Initailization!\n");
    return 1;
}
int sansec_destroy(ENGINE *e){
    SGD_RV rv = SDF_CloseDevice(hDeviceHandle);
    if (rv != SDR_OK){
        printf("CloseDevice err [0x%08x]\n", rv);
        return rv;
    }
    return 1;
}

//engine implementation
static const char *engine_sansec_id = "sansec";
static const char *engine_sansec_name = "sansec engine by billhan2016";
//bind function
int bind_helper(ENGINE *e, const char *id){
    if (!ENGINE_set_id(e, engine_sansec_id) 
        || !ENGINE_set_name(e, engine_sansec_name)
        || !ENGINE_set_init_function(e, sansec_init)
        || !ENGINE_set_destroy_function(e, sansec_destroy)
        //rand
        || !ENGINE_set_RAND(e, &sansec_random_method)
        //sm4
        || !ENGINE_set_ciphers(e, &sansec_ciphers)
        //sm3
        || !ENGINE_set_digests(e, &sansec_digests)
        //sm2
        //|| !ENGINE_set_EC(e, &sansec_engine_sm2_method)
        )
            return 0;
    return 1;
}


IMPLEMENT_DYNAMIC_CHECK_FN();
IMPLEMENT_DYNAMIC_BIND_FN(bind_helper);