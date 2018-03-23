#include <string.h>
#include<openssl/engine.h>
#include<openssl/ossl_typ.h>
#include<openssl/ecdsa.h>
#include "oezganEngine.h"

static const char *engine_oezgan_id = "oezgan";
static const char *engine_oezgan_name = "oezgan engine by FKIE";

//rand
int get_random_bytes(unsigned char *buffer, int num){
    printf("oezgan engine random length %d\n", num);
    memset(buffer, 1, num);
    return 99;
}

int oezgan_random_status(void){
    return 1;
}

RAND_METHOD oezgan_random_method = {
    NULL,
    get_random_bytes,
    NULL,
    NULL,
    NULL,
    oezgan_random_status
};
static int oezgan_engine_sha256_update(EVP_MD_CTX *ctx,const void *data,size_t count); 

//Digests
static int oezgan_engine_sha256_init(EVP_MD_CTX *ctx) {
    EVP_MD_CTX_set_update_fn(ctx, oezgan_engine_sha256_update);
    printf("initialized! SHA256\n");
    return 1;
}

static int oezgan_engine_sha256_update(EVP_MD_CTX *ctx,const void *data,size_t count) 
{
    printf("SHA256 update \n");
    return 1;
}

static int oezgan_engine_sha256_final(EVP_MD_CTX *ctx,unsigned char *md) {
    printf("SHA256 final\n");
    return 1;
}

int oezgan_engine_sha256_copy(EVP_MD_CTX *to, const EVP_MD_CTX *from)
{
    printf("SHA256 copy\n");
    return 1;
}

static int oezgan_engine_sha256_cleanup(EVP_MD_CTX *ctx) {
    printf("SHA256 cleanup\n");
    return 1;
}
static EVP_MD *sansec_sha256(int nid){
    EVP_MD *md;
    if(((md = EVP_MD_meth_new(nid, NID_sha256WithRSAEncryption)) == NULL)
        || !EVP_MD_meth_set_init(md, oezgan_engine_sha256_init)
        || !EVP_MD_meth_set_update(md, oezgan_engine_sha256_update)
        || !EVP_MD_meth_set_final(md, oezgan_engine_sha256_final)
        || !EVP_MD_meth_set_copy(md, oezgan_engine_sha256_copy)
        || !EVP_MD_meth_set_cleanup(md, oezgan_engine_sha256_cleanup)
        || !EVP_MD_meth_set_input_blocksize(md, 64)
        || !EVP_MD_meth_set_result_size(md, 32))
            EVP_MD_meth_free(md);
    return md;
}
static int oezgan_digest_ids[] = {NID_sha256};

static int oezgan_engine_digest_selector(ENGINE *e, const EVP_MD **digest,
        const int **nids, int nid) {
    int ok = 1;
    if (!digest) {
        *nids = oezgan_digest_ids;
        printf("\n Digest is empty! Nid:%d\n", nid);
        return 2;
    }
    printf("Digest nid %d requested\n",nid);
    if (nid == NID_sha256) {
        *digest = sansec_sha256(nid);
    }else {
        ok = 0;
        *digest = NULL;
    }
    return ok;
}

//ecdsa
static ECDSA_METHOD *oezgan_engine_ecdsa_method=NULL;

static int setup_ecdsa_method(void){
    oezgan_engine_ecdsa_method = ECDSA_METHOD_new(NULL);
    if(oezgan_engine_ecdsa_method = NULL) return 0;

    ECDSA_METHOD_set_name()
}


int oezgan_init(ENGINE *e){
    printf("Oezgan Engine Initailization!\n");
    return 603;
}

int bind_helper(ENGINE *e, const char *id){
    if (!ENGINE_set_id(e, engine_oezgan_id) ||
        !ENGINE_set_name(e, engine_oezgan_name)||
        !ENGINE_set_init_function(e, oezgan_init) ||
        !ENGINE_set_RAND(e, &oezgan_random_method) ||
        !ENGINE_set_digests(e, &oezgan_engine_digest_selector)
        )
            return 0;
    return 1;
}

IMPLEMENT_DYNAMIC_CHECK_FN();
IMPLEMENT_DYNAMIC_BIND_FN(bind_helper);

