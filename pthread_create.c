#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>

void* tfcn(void* arg){
    printf("thread: pid = %d, tid = %ld\n", getpid(), pthread_self());
}

int main(){
    pthread_t tid;
    printf("main: pid = %d, tid = %ld\n", getpid(), pthread_self());

    int ret = pthread_create(&tid, NULL, tfcn, NULL);
    if(ret < 0){
        perror("pthread_create error!\n");
        exit(1);
    }

    sleep(1);

    return 0;
}