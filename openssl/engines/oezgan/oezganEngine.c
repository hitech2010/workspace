#include <string.h>
#include<openssl/engine.h>
#include<openssl/ossl_typ.h>

static const char *engine_oezgan_id = "oezgan";
static const char *engine_oezgan_name = "oezgan engine by FKIE";

//rand
int get_random_bytes(unsigned char *buffer, int num){
    printf("oezgan engine random length %d\n", num);
    memset(buffer, 1, num);
    return 603;
}

int oezgan_random_status(void){
    return 1;
}

RAND_METHOD oezgan_random_method = {
    NULL,
    get_random_bytes,
    NULL,
    NULL,
    NULL,
    oezgan_random_status
};


int oezgan_init(ENGINE *e){
    printf("Oezgan Engine Initailization!\n");
    return 603;
}

int bind_helper(ENGINE *e, const char *id){
    if (!ENGINE_set_id(e, engine_oezgan_id) ||
        !ENGINE_set_name(e, engine_oezgan_name)||
        !ENGINE_set_init_function(e, oezgan_init) ||
        !ENGINE_set_RAND(e, &oezgan_random_method)
        )
            return 0;
    return 1;
}

IMPLEMENT_DYNAMIC_CHECK_FN();
IMPLEMENT_DYNAMIC_BIND_FN(bind_helper);

