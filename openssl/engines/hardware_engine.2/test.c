#include<openssl/engine.h>
#include "crypto/include/engine.h"
#include <string.h>

//测试hxy_engine引擎
int main(){
    ENGINE *e;
    int ret, num=20,i;
    char buf[20], *name;

    memset(buf, 0, num);

    ENGINE_load_hxycipher();

    e=ENGINE_by_id("engine_hxy");
    name=(char *)ENGINE_get_name(e);
    printf("engine name: %s\n", name);

    //generate rand number, this is a must, or will call the inner rand_xxx in openssl
    ret = RAND_set_rand_engine(e);
    if (ret!=1){
        printf("ENGINE_set_default_RAND failed\n");
        return -1;
    }
    ret = RAND_bytes((unsigned char*)buf, num);
    for(i=0; i<num; i++){
        printf("%d\t", (int)(buf[i])); 
    }
    printf("\n");
}