#include<openssl/engine.h>
#include "include/engine.h"
#include "include/algo.h"

//引擎实现。。。。。。。。。。。。。。。。。。
static int hxy_init(ENGINE *e){
    printf("call engine_init\n");
    return 1;
}
static int hxy_destory(ENGINE *e){
    printf("call engine_destroy\n");
    return 1;
}
static int hxy_finish(ENGINE *e){
    printf("call hxy_finish\n");
    return 1;
}
static int hxy_ctrl(ENGINE *e, int cmd, long i, void *p, void(*f)(void)){
    switch(cmd){
       default:
            printf("no real implementation\n");
            return -1; 
    }
    return 0;
}

static const ENGINE_CMD_DEFN hxy_cmd_defns[]={
    {ENGINE_CMD_BASE,
    "SO_PATH",
    "Specifies the path to the 'hxy' shared library",
    ENGINE_CMD_FLAG_STRING},
    {0, NULL, NULL, 0}
};

static int bind_helper(ENGINE *e){
    int ret;
    if (!ENGINE_set_id(e, engine_hxy_id) ||
        !ENGINE_set_name(e, engine_hxy_name) ||
        !ENGINE_set_RAND(e, &hxy_rand) ||
        !ENGINE_set_destroy_function(e, hxy_destory) ||
        !ENGINE_set_init_function(e, hxy_init) ||
        !ENGINE_set_finish_function(e, hxy_finish) ||
        !ENGINE_set_ctrl_function(e, hxy_ctrl) ||
        !ENGINE_set_cmd_defns(e, hxy_cmd_defns)
    ){
        printf("bind_helper failed, ENGINE_set_xxx err\n");
        return 0;
    }
    return 1;
}

static ENGINE *engine_hxycipher(void){
    ENGINE *e = ENGINE_new();
    if (!e) return NULL;
    if (!bind_helper(e)){
        ENGINE_free(e);
        return NULL;
    }
    return e; 
}

//绑定引擎相关函数，并讲引擎加入到openssl引擎列表中
void ENGINE_load_hxycipher(){
    ENGINE *e = engine_hxycipher();
    if (!e) return;
    ENGINE_add(e);
    ENGINE_free(e);
    ERR_clear_error();
}