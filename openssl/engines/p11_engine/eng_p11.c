/*****************************************
	pkcs11 engine demo

	filename:enginep11.c
    date:2005.08.12
	by eboy(eboymcy@163.com)
*****************************************/
#include <stdio.h>
#include <string.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/bn.h>
#include <openssl/engine.h>
#include <openssl/rsa.h>
#include <openssl/ossl_typ.h>
#include "eng_p11.h"


/****************************************************************************
 *			 Constants used when creating the ENGINE						*
 ***************************************************************************/
static const char *engine_p11_id = "pkcs11";
static const char *engine_p11_name = "pkcs11 engine support(by eboy)";


/****************************************************************************
 *			Functions to handle the engine									*
 ***************************************************************************/

/* Initiator which is only present to make sure this engine looks available */
static int p11_init(ENGINE *e)
{
    //printf("p11_init  OK.[FILE:%s,LINE:%d]\n",__FILE__,__LINE__);
    return 1;
}

/* Finisher which is only present to make sure this engine looks available */
static int p11_finish(ENGINE *e)
{
//  printf("p11_finish  OK.[FILE:%s,LINE:%d]\n",__FILE__,__LINE__);
    
    return 1;
}

/* Destructor (complements the "ENGINE_ncipher()" constructor) */
static int p11_destroy(ENGINE *e)
{
    
    //printf("p11_destroy  OK.[FILE:%s,LINE:%d]\n",__FILE__,__LINE__);

    
    return 1;
}




/****************************************************************************
 *			Engine commands													*
*****************************************************************************/
static const ENGINE_CMD_DEFN p11_cmd_defns[] = 
{
	{0, NULL, NULL, 0}
};


/****************************************************************************
 *			RSA functions													*
*****************************************************************************/
static int p11_public_encrypt(int len, const unsigned char *from,
                                 unsigned char *to, RSA *rsa, int padding)
{
    
    printf("\n**************public_encrypt, my function called, success!***********\n\n");
    return 0;
}

static int p11_private_decrypt(int len, const unsigned char *from,
                               unsigned char *to, RSA *rsa, int padding)
{
    return 0;
}

static RSA_METHOD *p11_rsa =
{
		"eboy's pkcs11 PKCS#1 RSA",
        p11_public_encrypt,
        NULL,
        NULL,
        p11_private_decrypt,
        NULL,
        NULL,
        NULL,
        NULL,
        0,
        NULL,
        NULL,
        NULL
};


/****************************************************************************
 *			Symetric cipher and digest function registrars					*
*****************************************************************************/

static int p11_ciphers(ENGINE *e, const EVP_CIPHER **cipher,
						  const int **nids, int nid);

static int p11_digests(ENGINE *e, const EVP_MD **digest,
						  const int **nids, int nid);


static int p11_cipher_nids[] ={ NID_des_cbc, NID_des_ede3_cbc, NID_desx_cbc, 0 };
static int p11_digest_nids[] ={ NID_md2, NID_md5, 0 };




/****************************************************************************
 *			Functions to handle the engine									*
*****************************************************************************/

static void ERR_load_P11_strings()
{
	//printf("ERR_load_P11_strings  OK.[FILE:%s,LINE:%d]\n",__FILE__,__LINE__);
	return;
	
}

static int bind_p11(ENGINE *e)
{
	//const RSA_METHOD *meth1;
	if(!ENGINE_set_id(e, engine_p11_id)
		|| !ENGINE_set_name(e, engine_p11_name)
		|| !ENGINE_set_RSA(e, &p11_rsa)
		//|| !ENGINE_set_ciphers(e, p11_ciphers)
		//|| !ENGINE_set_digests(e, p11_digests)
		|| !ENGINE_set_destroy_function(e, p11_destroy)
		|| !ENGINE_set_init_function(e, p11_init)
		|| !ENGINE_set_finish_function(e, p11_finish)
		/* || !ENGINE_set_ctrl_function(e, p11_ctrl) */
		/* || !ENGINE_set_cmd_defns(e, p11_cmd_defns) */)
		return 0;
	
	/* Ensure the p11 error handling is set up */
	ERR_load_P11_strings();
	return 1;
	}


#ifdef ENGINE_DYNAMIC_SUPPORT
static int bind_helper(ENGINE *e, const char *id)
{
	if(id && (strcmp(id, engine_p11_id) != 0))
		return 0;
	if(!bind_p11(e))
		return 0;
	return 1;
}       
IMPLEMENT_DYNAMIC_CHECK_FN()
IMPLEMENT_DYNAMIC_BIND_FN(bind_helper)
#else
static ENGINE *engine_p11(void)
{
	ENGINE *ret = ENGINE_new();
	if(!ret)
		return NULL;
	if(!bind_p11(ret))
	{
		ENGINE_free(ret);
		return NULL;
	}
	return ret;
}

void ENGINE_load_pkcs11(void)
{
	/* Copied from eng_[openssl|dyn].c */
	ENGINE *toadd = engine_p11();
	if(!toadd) return;
	ENGINE_add(toadd);
	ENGINE_free(toadd);
	ERR_clear_error();
}
#endif
