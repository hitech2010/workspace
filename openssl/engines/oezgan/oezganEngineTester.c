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
    //free(rand_buf);

    return 0;
}

