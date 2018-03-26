#include<openssl/engine.h>
#include<stdio.h>
#include<string.h>

void rand_test();
void sm3_test();
void sm4_encrypt();
void sm4_decrypt();

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
    printf("Engine successfully loaded\n");
    //ENGINE_remove(e);

    int r = ENGINE_init(e);
    printf("Engine name: %s,  init result: %d\n", ENGINE_get_name(e), r);
    //printf("Engine name: %s\n", ENGINE_get_name(e));

    //rand
    printf("*************************************\n");
    printf("************rand test****************\n");
    ENGINE_set_default_RAND(e);
    rand_test();

    //sm3
    printf("*************************************\n");
    printf("************sm3 test****************\n");
    ENGINE_set_default_digests(e);
    sm3_test();

    //sm4
    printf("*************************************\n");
    printf("************sm4 test****************\n");
    ENGINE_set_default_ciphers(e);
    sm4_encrypt();
    sm4_decrypt();

    return 0;
}
//*************rand test
void rand_test(){
    unsigned char rand_buf[5];
    int err = RAND_bytes(rand_buf, 5);
    hex_print("rand", rand_buf, 5);
}
//*************sm3 test
void sm3_test(){ 
    char *str="hello world!";
    int len = strlen(str);
    unsigned char digest[32]={0};
    int digestSize = -1;

    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    OPENSSL_assert(ctx != NULL);
    EVP_DigestInit_ex(ctx, EVP_sm3(), NULL);
    EVP_DigestUpdate(ctx, (unsigned char*)str, len);
    EVP_DigestFinal_ex(ctx, digest, &digestSize);

    hex_print("SM3 Digest", digest, digestSize);
    EVP_MD_CTX_free(ctx);
}
//************sm4 test
const unsigned char key[16] = {
    0xee, 0xbc, 0x1f, 0x57, 0x48, 0x7f, 0x51, 0x92, 0x1c, 0x04, 0x65, 0x66,
    0x5f, 0x8a, 0xe6, 0xd1
};
const unsigned char iv[16]={0};

void sm4_encrypt(){
    unsigned char *plaintext = "hello world!";
    int plainLen = strlen(plaintext);

    unsigned char encData[1024];
    int encl=0;
    int outl=0;

    //sm4 encrypt
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_sm4_ecb(), NULL, key, iv);
    EVP_EncryptUpdate(ctx, encData, &outl, plaintext, plainLen);
    encl = outl;
    EVP_EncryptFinal_ex(ctx, encData+outl, &outl);
    encl+=outl;

    hex_print("sm4 ciphertext", encData, encl);
    EVP_CIPHER_CTX_free(ctx);
}
void sm4_decrypt(){
    //encrypted "hello world!"
    const unsigned char ciphertext[]={
       0xc1,0xc3,0x26,0xd3,0xc6,0x3c,0x49,0xbc,0x5d,0x14,0x99,0xc4,0xfa,0x47,0xff,0x31
    };
    int cipherl = sizeof(ciphertext);

    unsigned char decData[1024];
    int outl=0;
    int decl=0;

    //sm4_decrypt
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_sm4_ecb(), NULL, key, iv);
    EVP_DecryptUpdate(ctx, decData, &outl, ciphertext, cipherl);
    decl = outl;
    EVP_DecryptFinal_ex(ctx, decData+outl, &outl);
    decl+=outl;
    decData[decl] = '\0';

   // hex_print("sm4 plaintext bytes:", decData, decl);
    printf("plaintext: %s\n", decData);
    
    EVP_CIPHER_CTX_free(ctx);
}
