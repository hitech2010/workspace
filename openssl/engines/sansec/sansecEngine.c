#include <string.h>
#include<openssl/engine.h>
#include<openssl/crypto.h>
#include<openssl/ossl_typ.h>
#include<openssl/evp.h>

int sansec_init(ENGINE *e);

/*sm3 functions*/
static int sansec_engine_sm3_init(EVP_MD_CTX *ctx);
static int sansec_engine_sm3_final(EVP_MD_CTX *ctx, unsigned char *md);
static int sansec_engine_sm3_update(EVP_MD_CTX *ctx, const void *data, size_t count);

/*rand number functions*/
int get_random_bytes(unsigned char *buffer, int num);


int get_random_bytes(unsigned char *buffer, int num){
    printf("sansec engine random length %d\n", num);
    memset(buffer, 1, num);
    return 1;
}

int sansec_random_status(void){
    return 1;
}

//sm3
static int sansec_engine_sm3_init(EVP_MD_CTX *ctx){
    EVP_MD_CTX_set_update_fn(ctx, &sansec_engine_sm3_update);
    printf("initialized SM3\n");
    return 1;
}
static int sansec_engine_sm3_update(EVP_MD_CTX *ctx, const void *data, size_t count){
    printf("SM3 update \n");
    unsigned char *digest = (unsigned char*)malloc(sizeof(unsigned char)*32);
    memset(digest, 2, 32);
    count = 32;
    //ctx->md_data = digest;
    void *md_data = EVP_MD_CTX_md_data(ctx);
    md_data = digest;
    return 1;
}
static int sansec_engine_sm3_final(EVP_MD_CTX *ctx, unsigned char *md){
    printf("SM3 final size of EVP_MD: %d\n", sizeof(EVP_MD *));
    //printf("SM3 final\n");
    memcpy(md, (unsigned char*)EVP_MD_CTX_md_data(ctx), 32);
    return 1;
}

static EVP_MD *sansec_engine_sm3_method = {
     NID_sm3,
     NID_undef,
     32,
     0,
     sansec_engine_sm3_init,
     sansec_engine_sm3_update,
     sansec_engine_sm3_final,
     NULL,
     NULL,
     NULL,
     NULL,
     {NID_undef, NID_undef, 0, 0, 0},
     64,
     32,
     NULL
};

RAND_METHOD sansec_random_method = {
    NULL,
    get_random_bytes,
    NULL,
    NULL,
    NULL,
    sansec_random_status
};

//sm3 digest selector function
static int sansec_digest_ids[]={NID_sm3};
static int sansec_engine_digest_selector(ENGINE *e, const EVP_MD **digest, const int **nids, int nid){
    int ok = 1;
    if(!digest){
        *nids=sansec_digest_ids;
        printf("\nDigest is empty! Nid:%d\n", nid);
        return 2;
    }
    printf("Digest no %d requested\n", nid);
    if (nid == NID_sm3){
        *digest = sansec_engine_sm3_method;
    }else{
        ok=0;
        *digest=NULL;
    }
    return ok;
}

//engine implementation
static const char *engine_sansec_id = "sansec";
static const char *engine_sansec_name = "sansec engine by billhan2016";
//bind function
int bind_helper(ENGINE *e, const char *id){
    if (!ENGINE_set_id(e, engine_sansec_id) ||
        !ENGINE_set_name(e, engine_sansec_name)||
        !ENGINE_set_init_function(e, sansec_init) ||
        //rand
        !ENGINE_set_RAND(e, &sansec_random_method) ||
        //sm3
        ENGINE_set_digests(e, &sansec_engine_digest_selector)
        )
            return 0;
    return 1;
}

//engine init
int sansec_init(ENGINE *e){
    printf("sansec Engine Initailization!\n");
    return 603;
}


IMPLEMENT_DYNAMIC_CHECK_FN();
IMPLEMENT_DYNAMIC_BIND_FN(bind_helper);