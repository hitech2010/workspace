#include<openssl/engine.h>
#include<openssl/ossl_typ.h>

/*
int main(void){
    ENGINE_load_builtin_engines();
    ENGINE *e = ENGINE_get_first();
    while(e){
        printf("%s\n", ENGINE_get_name(e));
        ENGINE *t = ENGINE_get_next(e);
        ENGINE_free(e);
        e = t;
    }
    
    return 0;
}
*/

int main(){
    ENGINE *e = ENGINE_by_id("rdrand");
    const RAND_METHOD *rand = ENGINE_get_RAND(e);
}