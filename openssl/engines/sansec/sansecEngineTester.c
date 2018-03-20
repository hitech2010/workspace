#include<openssl/engine.h>
#include<stdio.h>
#include<string.h>


void hex_print(const char* type, const unsigned char* buf, size_t len){
    fprintf(stdout, "%s: ", type);
    size_t i;
    for(i=0; i<len; i++){
        printf("0x%02x", buf[i]);
        if(i<len-1)
            printf(",");
    }
    printf("\n");
}

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

    //int r = ENGINE_init(e);
    //printf("Engine name: %s,  init result: %d\n", ENGINE_get_name(e), r);
    printf("Engine name: %s\n", ENGINE_get_name(e));

    //rand
    ENGINE_set_default_RAND(e);
    unsigned char rand_buf[5];
    int err = RAND_bytes(rand_buf, 5);
    hex_print("rand", rand_buf, 5);

    //sm3
    char *str="hello world!";
    int len = strlen(str);
    int rv = ENGINE_set_default_digests(e);
    printf("ENGINE Setting Defulat Digests %d\n", rv);

    unsigned char digest[32];
    int digestSize = -1;
    EVP_MD_CTX *sm3_ctx = EVP_MD_CTX_new();
    rv = EVP_DigestInit_ex(sm3_ctx, EVP_sm3(), e);
    printf("DigestInit %d\n", rv);
    rv = EVP_DigestUpdate(sm3_ctx, str, len);
    printf("DigestUpdate %d\n", rv);
    rv = EVP_DigestFinal_ex(sm3_ctx, digest, &digestSize);
    printf("DigestFinal %d\n", rv);

    hex_print("SM3 Digest", digest, digestSize);
    //EVP_MD_CTX_free(sm3_ctx);
    EVP_MD_CTX_destroy(sm3_ctx);

    return 0;
}
