#include <openssl/evp.h>
#include <string.h>

#define SHA512_DIGEST_LENGTH 64 

void TEST_EVP_SHA512();

static void hex_print(const char *name, const unsigned char *buf, size_t len){
    size_t i;
    fprintf(stderr, "%s ", name);
    for (i=0; i<len; i++){
        fprintf(stderr, "%02X", buf[i]);
    }
    fputs("\n", stderr);
}
void TEST_EVP_SHA512(){
    //initialize md ctx
    EVP_MD_CTX *ctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(ctx, EVP_sha512(), NULL);
    char *data = (char*)"hello";
    unsigned int len = strlen(data);
    //compute hash
    EVP_DigestUpdate(ctx, data, len);
    unsigned char result[SHA512_DIGEST_LENGTH]={0};
    EVP_DigestFinal(ctx, result, &len);
    //print
    hex_print("sha512", result, SHA512_DIGEST_LENGTH);


    //using one func
    unsigned char result2[SHA512_DIGEST_LENGTH]={0};
    EVP_Digest("hello", 5, result2, NULL, EVP_sha512(), NULL);
    hex_print("sha512", result2, SHA512_DIGEST_LENGTH);
}
int main(){
    TEST_EVP_SHA512();
    return 0;
}
