#include<openssl/ecdsa.h>
#include<openssl/ossl_typ.h>
#include<openssl/evp.h>
#include<openssl/bn.h>
#include<string.h>


void main(){
    const char *message = "hello world!";
    unsigned char digest[EVP_MAX_MD_SIZE];
    int digestl;

//get the message digest
    EVP_MD_CTX *md_ctx = EVP_MD_CTX_new();
    EVP_DigestInit(md_ctx,EVP_sha256());
    EVP_DigestUpdate(md_ctx, (unsigned char*)message, strlen(message));
    EVP_DigestFinal(md_ctx, digest, &digestl);

    int i=0;
    for(i=0; i<digestl; i++){
        printf("%02x ", digest[i]);
    }
    printf("\n");
//create the key
    EC_KEY *key = EC_KEY_new_by_curve_name(NID_sm2);
    //EC_KEY *key = EC_KEY_new_by_curve_name(NID_X9_62_prime256v1);
    if(key == NULL) {
        printf("ec_key_new_by_curve_name err\n");
        goto error;
    }
    EC_KEY_generate_key(key);
    if(!EC_KEY_check_key(key)){
        printf("EC_KEY_check_key failed\n");
    }

//create the signature
    BIGNUM *r =NULL, *s=NULL;
    BIGNUM *kinv = NULL, *rp = NULL;
    ECDSA_sign_setup(key, NULL, &kinv, &rp);
    ECDSA_SIG *signature = ECDSA_do_sign_ex(digest, digestl, kinv, rp, key);
    //ECDSA_SIG *signature = ECDSA_do_sign(digest, digestl, key);
    if (signature == NULL){
        printf("ecdsa_do_sign_ex err\n");
        goto error;
    } 
    ECDSA_SIG_get0(signature, &r, &s);
    BN_print_fp(stdout, r); printf("\n");
    BN_print_fp(stdout, s); printf("\n");

/*
    EC_POINT *pt = EC_KEY_get0_public_key(key);
    EC_KEY *pub = EC_KEY_new();
    EC_KEY_set_public_key(pub, pt);
    int ok = ECDSA_do_verify(digest, digestl, signature, pub);
*/

    int ok = ECDSA_do_verify(digest, digestl, signature, key);
    if (ok != 1) goto error;

    printf("verify? %s\n", ok==1? ":-)": ":-(");

    error:
    EC_KEY_free(key);
    ECDSA_SIG_free(signature);
    EVP_MD_CTX_free(md_ctx);
    BN_clear_free(kinv);
    BN_clear_free(rp);
    return;
}