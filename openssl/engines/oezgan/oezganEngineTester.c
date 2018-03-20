#include<openssl/engine.h>
#include<stdio.h>
#include<string.h>

int main(){
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();

    ENGINE_load_dynamic();
    ENGINE *e = ENGINE_by_id("dynamic");
    ENGINE_ctrl_cmd_string(e, "SO_PATH", "./oezganEngine.so", 0);
    ENGINE_ctrl_cmd_string(e, "ID", "oezgan", 0);
    ENGINE_ctrl_cmd_string(e, "LOAD", NULL, 0);

    if (e == NULL){
        printf("Cound not Load Oezgan Engine\n");
        exit(1);
    }
    printf("Oezgan Engine successfully loaded\n");

    int r = ENGINE_init(e);
    printf("Engine name: %s,  init result: %d\n", ENGINE_get_name(e), r);

    //rand
    ENGINE_set_default_RAND(e);
    unsigned char rand_buf[5];
    int err = RAND_bytes(rand_buf, 5);
    for(int i=0; i<5; i++){
        printf("%x", rand_buf[i]);
    }
    printf("\n");

    //digest
    char * str = "Fraunhofer FKIE Wachtberg!";
    int str_len =  strlen(str);
    int er = ENGINE_set_default_digests(e);
    printf("ENGINE SETTING DEFAULT DIGESTS %d\n",er);

    unsigned char digest[32];
    unsigned int digestSize = -1;

    EVP_MD_CTX *evp_ctx;
    //evp_ctx = EVP_MD_CTX_create();
    evp_ctx = EVP_MD_CTX_new();

    er = EVP_DigestInit(evp_ctx, EVP_sha256());
    printf("Digest INIT %d\n",er);
/*
    er = EVP_DigestUpdate(evp_ctx, (unsigned char*)str, str_len);
    printf("Digest Update %d\n",er);
    er = EVP_DigestFinal(evp_ctx, digest, &digestSize);
    printf("Digest Final %d Digest size:%d\n",er,digestSize);
    for(int i= 0; i< digestSize; i++) {
        printf("%x", digest[i]);
    }
    printf("\n");
    */
    EVP_MD_CTX_destroy(evp_ctx);
    return 0;
}

