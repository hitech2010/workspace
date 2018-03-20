/*****************************************
	sansec engine demo

	by hxy(hanxueyang@sansec.com.cn)
*****************************************/
#include <stdio.h>
#include <string.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/bn.h>
#include <openssl/engine.h>
#include <openssl/rsa.h>
#include "eng_sansec.h"


/****************************************************************************
 *			 Constants used when creating the ENGINE						*
 ***************************************************************************/
static const char *engine_sansec_id = "sansec";
static const char *engine_sansec_name = "sansec engine support(by hxy)";

/****************************************************************************
 *			Functions to handle the engine									*
 ***************************************************************************/

/* Initiator which is only present to make sure this engine looks available */
static int sansec_init(ENGINE *e)
{
    //printf("sansec_init  OK.[FILE:%s,LINE:%d]\n",__FILE__,__LINE__);
    return 1;
}
/* Finisher which is only present to make sure this engine looks available */
static int sansec_finish(ENGINE *e)
{
//  printf("sansec_finish  OK.[FILE:%s,LINE:%d]\n",__FILE__,__LINE__);
    return 1;
}
/* Destructor (complements the "ENGINE_ncipher()" constructor) */
static int sansec_destroy(ENGINE *e)
{
    //printf("sansec_destroy  OK.[FILE:%s,LINE:%d]\n",__FILE__,__LINE__);
    return 1;
}
/****************************************************************************
 *			Engine commands													*
*****************************************************************************/
static const ENGINE_CMD_DEFN sansec_cmd_defns[] = 
{
	{0, NULL, NULL, 0}
};


/****************************************************************************
 *			RSA functions													*
*****************************************************************************/
static int sansec_public_encrypt(int len, const unsigned char *from,
                                 unsigned char *to, RSA *rsa, int padding)
{
	printf("\n call sansec_public_encrypt\n\n");
    return 0;
}

static int sansec_private_decrypt(int len, const unsigned char *from,
                               unsigned char *to, RSA *rsa, int padding)
{
	printf("\n call sansec_private_decrypt\n\n");
    return 0;
}

static RSA_METHOD *sansec_rsa =
{
		"sansec-RSA",
        sansec_public_encrypt,
        NULL,
        NULL,
        sansec_private_decrypt,
        NULL,
        NULL,
        NULL,
        NULL,
        0,
        NULL,
        NULL,
        NULL,
		NULL,
};


/****************************************************************************
 *			Symetric cipher and digest function registrars					*
*****************************************************************************/

static int sansec_ciphers(ENGINE *e, const EVP_CIPHER **cipher,
						  const int **nids, int nid);

static int sansec_digests(ENGINE *e, const EVP_MD **digest,
						  const int **nids, int nid);


static int sansec_cipher_nids[] ={ NID_des_cbc, NID_des_ede3_cbc, NID_desx_cbc, 0 };
static int sansec_digest_nids[] ={ NID_md2, NID_md5, 0 };




/****************************************************************************
 *			Functions to handle the engine									*
*****************************************************************************/

static void ERR_load_SANSEC_strings()
{
	//printf("ERR_load_P11_strings  OK.[FILE:%s,LINE:%d]\n",__FILE__,__LINE__);
	return;
	
}

static int bind_sansec(ENGINE *e)
{
	//const RSA_METHOD *meth1;
	if(!ENGINE_set_id(e, engine_sansec_id)
		|| !ENGINE_set_name(e, engine_sansec_name)
		|| !ENGINE_set_RSA(e, sansec_rsa)
		|| !ENGINE_set_ciphers(e, sansec_ciphers)
		|| !ENGINE_set_digests(e, sansec_digests)
		|| !ENGINE_set_destroy_function(e, sansec_destroy)
		|| !ENGINE_set_init_function(e, sansec_init)
		|| !ENGINE_set_finish_function(e, sansec_finish)
		//|| !ENGINE_set_ctrl_function(e, sansec_ctrl) 
		|| !ENGINE_set_cmd_defns(e, sansec_cmd_defns) )
		return 0;
	
	/* Ensure the sansec error handling is set up */
	ERR_load_SANSEC_strings();
	return 1;
	}


#ifdef ENGINE_DYNAMIC_SUPPORT
static int bind_helper(ENGINE *e, const char *id)
{
	if(id && (strcmp(id, engine_sansec_id) != 0))
		return 0;
	if(!bind_sansec(e))
		return 0;
	return 1;
}       
IMPLEMENT_DYNAMIC_CHECK_FN()
IMPLEMENT_DYNAMIC_BIND_FN(bind_helper)
#else
static ENGINE *engine_sansec(void)
{
	ENGINE *ret = ENGINE_new();
	if(!ret)
		return NULL;
	if(!bind_sansec(ret))
	{
		ENGINE_free(ret);
		return NULL;
	}
	return ret;
}

void ENGINE_load_pkcs11(void)
{
	/* Copied from eng_[openssl|dyn].c */
	ENGINE *toadd = engine_sansec();
	if(!toadd) return;
	ENGINE_add(toadd);
	ENGINE_free(toadd);
	ERR_clear_error();
}
#endif
