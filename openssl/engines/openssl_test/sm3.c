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

//sm3 test
#define SM3_DIGEST_LENGTH 32
void sm3_test(){
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(ctx, EVP_sm3(), NULL);

    const char *data = "hello";
    unsigned char *res[SM3_DIGEST_LENGTH];
    unsigned int len = strlen(data);

    //compute hash
    EVP_DigestUpdate(ctx, data, len);
    EVP_DigestFinal(ctx, res, &len);
    //print
    hex_print("sm3", res, SM3_DIGEST_LENGTH); 
}

//sm4 test
#define SM4_BLOCKSIZE 16
const unsigned char sm4_key[] = {
    0xee, 0xbc, 0x1f, 0x57, 0x48, 0x7f, 0x51, 0x92, 0x1c, 0x04, 0x65, 0x66,
    0x5f, 0x8a, 0xe6, 0xd1
};
void sm4_encrypt(){
    const unsigned char plaintext[]={
        0x4d, 0x23, 0xc3, 0xce, 0xc3, 0x34, 0xb4, 0x9b, 0xdb, 0x37, 0x0c, 0x43,
        0x7f, 0xec, 0x78, 0xde
    };
    unsigned char ciphertext[sizeof(plaintext)];
    unsigned int outl;
    //sm4 encrypt
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

    EVP_EncryptInit_ex(ctx, EVP_sm4_ecb(), NULL, sm4_key, NULL);
    EVP_EncryptUpdate(ctx, ciphertext, &outl, plaintext, sizeof(plaintext));
    EVP_EncryptFinal_ex(ctx, ciphertext, &outl); //a must

    hex_print("sm4 ciphertext", ciphertext, outl);
    EVP_CIPHER_CTX_free(ctx);
}
void sm4_decrypt(){
    const unsigned char ciphertext[]={
        0x68,0x04,0xfa,0x7f,0xec,0xd1,0xb9,0xe3,0x92,0x23,0x4e,0xeb,0x48,0x29,0x11,0xe7
    };
    unsigned char plaintext[sizeof(ciphertext)];
    unsigned int outl;
    //sm4_decrypt
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();

    EVP_DecryptInit_ex(ctx, EVP_sm4_ecb(), NULL, sm4_key, NULL);
    /*
    EVP_DecryptUpdate(ctx, plaintext, &outl, ciphertext, sizeof(ciphertext));
    EVP_DecryptFinal_ex(ctx, plaintext, &outl);
    printf("outl: %d\n", outl);
    hex_print("sm4 plaintext", plaintext, outl);
    */
    EVP_DecryptUpdate(ctx, plaintext, &outl, ciphertext, sizeof(ciphertext));
    EVP_DecryptFinal_ex(ctx, plaintext, &outl);

    hex_print("sm4 plaintext", plaintext, outl);
    EVP_CIPHER_CTX_free(ctx);
}

//main func
int main(){
    //sm3_test();
    sm4_encrypt(); 
    sm4_decrypt();
    return 0;
}
