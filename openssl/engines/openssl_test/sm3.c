#include <openssl/evp.h>
#include <string.h>
#include <openssl/modes.h>

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

//sm3 test ****************
#define SM3_DIGEST_LENGTH 32
void sm3_test(){
    const char *data = "hello";
    unsigned char *res[SM3_DIGEST_LENGTH];
    unsigned int len = strlen(data);

    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    //compute sm3 hash
    EVP_DigestInit_ex(ctx, EVP_sm3(), NULL);
    EVP_DigestUpdate(ctx, data, len);
    EVP_DigestFinal(ctx, res, &len);
    //print
    hex_print("sm3", res, SM3_DIGEST_LENGTH); 
    EVP_MD_CTX_free(ctx);
}

//sm4 test **********************
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

    EVP_EncryptInit_ex(ctx, EVP_sm4_ecb(), NULL, key, NULL);
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

    EVP_DecryptInit_ex(ctx, EVP_sm4_ecb(), NULL, key, NULL);
    EVP_DecryptUpdate(ctx, decData, &outl, ciphertext, cipherl); 
    decl = outl;
    EVP_DecryptFinal_ex(ctx, decData+outl, &outl);
    decl+=outl;
    decData[decl] = '\0';

    hex_print("sm4 plaintext bytes:", decData, decl);
    printf("plaintext: %s\n", decData);
    EVP_CIPHER_CTX_free(ctx);
}

//main func
int main(){
    //sm3_test();
    sm4_encrypt(); 
    sm4_decrypt();
    return 0;
}
