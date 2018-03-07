#include <openssl/engine.h>
#include <stdio.h>
#include <string.h>

int main(int argc, const char* argv[] ) {
    //OpenSSL_add_all_algorithms();

    //ERR_load_crypto_strings();

    ENGINE_load_dynamic();
    ENGINE *octeon_engine = ENGINE_by_id("dynamic");
    ENGINE_ctrl_cmd_string(octeon_engine, "SO_PATH", "../dyn_nuron.so", 0);
    ENGINE_ctrl_cmd_string(octeon_engine, "ID", "octeon", 0);
    ENGINE_ctrl_cmd_string(octeon_engine, "LOAD", NULL, 0);


    if( octeon_engine == NULL )
    {
        printf("Could not Load Oezgan Engine!\n");
        exit(1);
    }
    printf("Oezgan Engine successfully loaded\n");

    int init_res = ENGINE_init(octeon_engine);
    printf("Engine name: %s init result : %d \n",ENGINE_get_name(octeon_engine), init_res);

    unsigned long e  = RSA_3;
    int bits=512;
    RSA *r = RSA_generate_key(bits, e, NULL, NULL);
    RSA_print_fp(stdout, r, 11);
    
    return 0;
}

