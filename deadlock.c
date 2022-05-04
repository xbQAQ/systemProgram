#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>

pthread_mutex_t a, b;

void* tfunc(void* arg){
    printf("------------tfnc:-----------\n");
    pthread_mutex_lock(&b);
    printf("get B\n");
    sleep(1);
    pthread_mutex_lock(&a);
    printf("get A\n");
    printf("pthread: get a and b lock\n");
    pthread_mutex_unlock(&a);
    pthread_mutex_unlock(&b);
    printf("------------tfnc:-----------\n");
    return NULL;
}

int main(){
    int ret = pthread_mutex_init(&a, NULL); //初始化 a 互斥锁
    if(ret != 0){
        fprintf(stderr, "pthread_mutex_init a error!\n");
        exit(1);
    }
    ret = pthread_mutex_init(&b, NULL); //初始化 b 互斥锁
    if(ret != 0){
        fprintf(stderr, "pthread_mutex_init b error!\n");
        exit(1);
    }

    pthread_t tid;
    pthread_attr_t attr;
    ret = pthread_attr_init(&attr);
    if(ret != 0){
        fprintf(stderr, "pthread_attr_init error!\n");
        exit(1);
    }

    ret = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if(ret != 0){
        fprintf(stderr, "pthread_attr_setdetachstate error!\n");
        exit(1);
    }

    ret = pthread_create(&tid, &attr, tfunc, NULL);
    if(ret != 0){
        fprintf(stderr, "pthread_create error!\n");
        exit(1);
    }

    ret = pthread_attr_destroy(&attr);
    if(ret != 0){
        fprintf(stderr, "pthread_attr_destroy error!\n");
        exit(1);
    }

    /*-----------主线程------------*/
    printf("------------Main:-----------\n");
    pthread_mutex_lock(&a);
    printf("get A\n");
    sleep(1);
    pthread_mutex_lock(&b);
    printf("get B\n");
    printf("Main: get a and b lock\n");
    pthread_mutex_unlock(&a);
    pthread_mutex_unlock(&b);
    printf("------------Main:-----------\n");
    /*-----------主线程------------*/
    
    ret = pthread_join(tid, NULL);
    if(ret != 0){
        fprintf(stderr, "pthread_join error!\n");
        exit(1);
    }

    ret = pthread_mutex_destroy(&a);
    if(ret != 0){
        fprintf(stderr, "pthread_mutex_destroy a error!\n");
        exit(1);
    }
    ret = pthread_mutex_destroy(&b);
    if(ret != 0){
        fprintf(stderr, "pthread_mutex_destroy b error!\n");
        exit(1);
    }
    return 0;
}