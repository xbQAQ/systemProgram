#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>

void* tfcn(void* arg){
    printf("thread: pthread: my pthread id is %ld\n", pthread_self());
    return NULL;
}

int main(){
    int ret;
    pthread_t tid;
    pthread_attr_t attr;
    ret = pthread_attr_init(&attr);       //初始化属性
    if(ret != 0){
        fprintf(stderr, "pthread_attr_init error: %s\n", strerror(ret));
    }

    ret = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);  //设置属性为分离属性
    if(ret != 0){
        fprintf(stderr, "pthread_attr_setdetachstate error: %s\n", strerror(ret));
    }

    ret = pthread_create(&tid, &attr, tfcn, NULL);   //创建线程为分离线程
    if(ret != 0){
        fprintf(stderr, "pthread_create error: %s\n", strerror(ret));
    }

    ret = pthread_attr_destroy(&attr);      //销毁属性
    if(ret != 0){
        fprintf(stderr, "pthread_attr_destroy error: %s\n", strerror(ret));
    }

    printf("thread: pthread: my pthread id is %ld\n", pthread_self());

    ret = pthread_join(tid, NULL);
    if(ret != 0){
        fprintf(stderr, "pthread_join error: %s\n", strerror(ret));
    }

    pthread_exit(NULL);     //退出线程
    return 0;
}