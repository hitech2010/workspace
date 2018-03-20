#include <string.h>
#include<openssl/engine.h>
#include<openssl/ossl_typ.h>

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

//Digests
static int oezgan_engine_sha256_init(EVP_MD_CTX *ctx) {
    //EVP_MD_CTX_update_fn(ctx);
    printf("initialized! SHA256\n");
    return 1;
}

static int oezgan_engine_sha256_update(EVP_MD_CTX *ctx,const void *data,size_t count) 
{
    printf("SHA256 update \n");
    unsigned char * digest256 = (unsigned char*) malloc(sizeof(unsigned char)*32);
    memset(digest256,2,32);
    count = 32;
    unsigned char *md_data = EVP_MD_CTX_md_data(ctx);
    md_data = digest256;
    return 1;
}

static int oezgan_engine_sha256_final(EVP_MD_CTX *ctx,unsigned char *md) {
    printf("SHA256 final size of EVP_MD: %d\n", sizeof(EVP_MD *));
    memcpy(md,(unsigned char*)EVP_MD_CTX_md_data(ctx),32);
    return 1;
}

int oezgan_engine_sha256_copy(EVP_MD_CTX *to, const EVP_MD_CTX *from)
{
    printf("Copy SHA256\n");
    if (EVP_MD_CTX_md_data(to) && EVP_MD_CTX_md_data(from)) {
        memcpy(EVP_MD_CTX_md_data(to), EVP_MD_CTX_md_data(from),sizeof(EVP_MD_CTX_md_data(from)));
    }
    return 1;
}

static int oezgan_engine_sha256_cleanup(EVP_MD_CTX *ctx) {
    printf("SHA256 cleanup\n");
    if (EVP_MD_CTX_md_data(ctx))
        memset(EVP_MD_CTX_md_data(ctx), 0, 32);
    return 1;
}
static EVP_MD *oezgan_engine_sha256_method=  {
        NID_sha256,
        NID_undef,
        32,
        //EVP_MD_FLAG_PKEY_METHOD_SIGNATURE,
        0,
        oezgan_engine_sha256_init,
        oezgan_engine_sha256_update,
        oezgan_engine_sha256_final,
        oezgan_engine_sha256_copy,
        oezgan_engine_sha256_cleanup,
        /* FIXME: prototype these some day */
        NULL,
        NULL,
        {NID_undef, NID_undef, 0, 0, 0},
        64, /*Block Size*/
        32, /* how big does the ctx->md_data need to be */
        /* control function */
        NULL,
};
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
        printf("use oezgan_engine_sha256_method\n");
       *digest = oezgan_engine_sha256_method;
    }else {
        ok = 0;
        *digest = NULL;
    }
    return ok;
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

