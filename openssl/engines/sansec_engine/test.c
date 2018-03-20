//test.c
#include <stdio.h>
#include <string.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/bn.h>
#include <openssl/engine.h>
#include "eng_sansec.h"

static void display_engine_list()
{
	ENGINE *h;
	int loop;
	
	h = ENGINE_get_first();
	loop = 0;
	printf("listing available engine types\n");
	while(h)
	{
		printf("engine %i, id = \"%s\", name = \"%s\"\n",
			loop++, ENGINE_get_id(h), ENGINE_get_name(h));
		h = ENGINE_get_next(h);
	}
	printf("end of list\n");
	/* ENGINE_get_first() increases the struct_ref counter, so we 
	must call ENGINE_free() to decrease it again */
	ENGINE_free(h);
}


void test()
{
	ENGINE *sansec_engine = NULL;
	int rv;
	unsigned char buf[1024];
	RSA *rsa;
	EVP_PKEY *evpKey;
	
	ENGINE_load_sansec();
	//display_engine_list();
	
	sansec_engine = ENGINE_by_id("sansec");
	if(sansec_engine == NULL)
	{
		printf("get sansec engine Error\n");
		return ;
	}
	printf("get sansec engine OK.name:%s\n",ENGINE_get_name(sansec_engine));
	ENGINE_register_RSA(sansec_engine);
	rv = ENGINE_set_default(sansec_engine,ENGINE_METHOD_ALL);
	evpKey = EVP_PKEY_new();
	rsa = RSA_generate_key(1024,RSA_F4,NULL,NULL);
	rv = EVP_PKEY_set1_RSA(evpKey,rsa);
	
	//rv = EVP_PKEY_encrypt(buf,buf,128,evpKey);
	
	rv = ENGINE_finish(sansec_engine);
	
	rv = ENGINE_free(sansec_engine);
	printf("test end.\n");
	return;
}
int main()
{
	test();
	return 0;
}