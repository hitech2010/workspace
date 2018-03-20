#include<openssl/engine.h>
#include<stdio.h>
#include<string.h>

int main(){
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();

    ENGINE_load_dynamic();
    ENGINE *e = ENGINE_by_id("dynamic");
    ENGINE_ctrl_cmd_string(e, "SO_PATH", "./sansecEngine.so", 0);
    ENGINE_ctrl_cmd_string(e, "ID", "sansec", 0);
    ENGINE_ctrl_cmd_string(e, "LOAD", NULL, 0);

    if (e == NULL){
        printf("Cound not Load sansec Engine\n");
        exit(1);
    }
    printf("sansec Engine successfully loaded\n");

    int r = ENGINE_init(e);
    printf("Engine name: %s,  init result: %d\n", ENGINE_get_name(e), r);

    //rand****************************************
    ENGINE_set_default_RAND(e);
    unsigned char rand_buf[5];
    int err = RAND_bytes(rand_buf, 5);
    for(int i=0; i<5; i++){
        printf("%x", rand_buf[i]);
    }
    printf("\n");

    //sm3*****************************************
    char *str = "Hello billhan2016";
    int str_len = strlen(str);
    r = ENGINE_set_default_digests(e);
    printf("Engine set default digests %d\n", r);

    unsigned char digest[32];
    unsigned int digestSize = -1;

    EVP_MD_CTX *evp_ctx;
    evp_ctx = EVP_MD_CTX_create();
    r = EVP_DigestInit_ex(evp_ctx, EVP_sm3(),e);
    printf("Digest INIT %d\n",r);
    r = EVP_DigestUpdate(evp_ctx, (unsigned char*)str, str_len);
    printf("Digest Update %d\n",r);
    r = EVP_DigestFinal(evp_ctx, digest, &digestSize);
    printf("Digest Final %d Digest size:%d\n",r,digestSize);
    for(int i= 0; i< digestSize; i++) {
        printf("%x", digest[i]);
    }
    printf("\n");
    EVP_MD_CTX_destroy(evp_ctx);

    //ENGINE_free(e);
    return 0;
}

