#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>

struct A{
    int val;
    char arr[256];
};

void* tfcn(void* arg){
    struct A* pa = (struct A*)arg;
    pa->val = 1;
    strcpy(pa->arr, "hello");
    return (void*)pa;
}

int main(){
    pthread_t tid;
    struct A a;
    int ret = pthread_create(&tid, NULL, tfcn, (void*)&a);
    if(ret < 0){
        perror("pthread create error!\n");
        exit(1);
    }

    struct A* pa;
    pthread_join(tid, (void**)&pa);
    printf("pa->val is %d, pa->char[256] is %s\n", pa->val, pa->arr);
    //free(pa);

    pthread_exit(0);

    return 0;
}