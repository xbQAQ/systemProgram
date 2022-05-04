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
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, tfcn, NULL);
    if(ret != 0){
        fprintf(stderr, "pthread_create error: %s\n", strerror(ret));
        exit(1);    //退出当前进程
    }

    ret = pthread_detach(tid);
    if(ret != 0){
        fprintf(stderr, "pthread_detach error: %s\n", strerror(ret));
        exit(1);    //退出当前进程
    }

    //错误：线程分离后，线程终止，会自动清理pcb，无需回收，不用主线程回收
    ret = pthread_join(tid, NULL);
    if(ret != 0){
        fprintf(stderr, "pthread_join error: %s\n", strerror(ret));
        exit(1);    //退出当前进程
    }

    printf("Main: pthread: my pthread id is %ld\n", pthread_self());

    pthread_exit(0);

    return 0;
}