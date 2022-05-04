#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>

void* tfcn(void* arg){
    while(1){
        pthread_testcancel();       //设置取消点
    }
    return NULL;
}

int main(){
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, tfcn, NULL);
    if(ret != 0){
        fprintf(stderr, "pthread_create error: %s\n", strerror(ret));
    }

    sleep(3);

    ret = pthread_cancel(tid);  //杀死线程，异常退出
    if(ret != 0){
        fprintf(stderr, "pthread_cancel error: %s\n", strerror(ret));
    }

    int* retval;
    ret = pthread_join(tid, (void**)&retval);
    printf("return value is %d\n", (int)retval);    //异常退出，返回-1
    if(ret != 0){
        fprintf(stderr, "pthread_join error: %s\n", strerror(ret));
    }

    pthread_exit(NULL);     //退出线程
    return 0;
}