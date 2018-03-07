#include<openssl/rand.h>
#include<openssl/engine.h>

//密码函数实现。。。。。。。。。。。。
static int hxy_get_random_bytes(unsigned char *buf, int num){
    int i;
    printf("call hw_get_random_bytes\n");
    for (i=0; i<num; i++){
        memset(buf++, i, 1);
    } 
    return 1;
}

static RAND_METHOD hxy_rand = {
    NULL,
    hxy_get_random_bytes,
    NULL,
    NULL,
    NULL,
    NULL,
};

//引擎实现。。。。。。。。。。。。。。。。。。
static const char *engine_hxy_id = "engine_hxy";
static const char *engine_hxy_name = "engineTest";

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