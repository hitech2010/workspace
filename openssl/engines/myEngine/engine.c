#include <openssl/engine.h>
#include <openssl/ossl_typ.h>

#define SM3_DIGEST_LENGTH 256
static const char *engine_e_sm3_id = "sm3";
static const char *engine_e_sm3_name = "SANSEC SM3 engine";
static int bind_help(ENGINE *e){
    if (!ENGINE_set_id(e, engine_e_sm3_id) ||
    !ENGINE_set_name(e, engine_e_sm3_name))
        return 0;
    return 1;
}
static ENGINE *ENGINE_sm3(void){
    ENGINE *ret = ENGINE_new();
    if (ret == NULL) returen NULL;
    if (!bind_helper(ret)){
        ENGINE_free(ret);
        return NULL;
    }
    return ret;
}

const EVP_MD *sansec_sm3={
    NID_sm3,
    NID_sm3WithRSAEncryption,
   SM3_DIGEST_LENGTH,
   NULL,
   sm3_digest_init,
   sm3_digest_update,
   sm3_digest_final,
   NULL,
   NULL,
   EVP_PKEY_RSA,
   NULL,
   100,  //CTX SIZE, todo 
};