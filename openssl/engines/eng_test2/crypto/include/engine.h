#ifndef _ENGINE_H
#define _ENGINE_H

#include<openssl/engine.h>

//引擎实现。。。。。。。。。。。。。。。。。。
static const char *engine_hxy_id = "engine_hxy";
static const char *engine_hxy_name = "engineTest";

//绑定引擎相关函数，并讲引擎加入到openssl引擎列表中
void ENGINE_load_hxycipher();

#endif