#include<openssl/rand.h>
#include "include/algo.h"

//密码函数实现。。。。。。。。。。。。
static int hxy_get_random_bytes(unsigned char *buf, int num){
    int i;
    printf("call hw_get_random_bytes\n");
    for (i=0; i<num; i++){
        memset(buf++, i, 1);
    } 
    return 1;
}

static RAND_METHOD hxy_rand = {
    NULL,
    hxy_get_random_bytes,
    NULL,
    NULL,
    NULL,
    NULL,
};