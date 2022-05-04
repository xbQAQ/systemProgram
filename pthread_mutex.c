#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>

pthread_mutex_t mutex;

void* tfcn(void* arg){
    while(1){
        pthread_mutex_lock(&mutex);

        printf("HELLO ");
        sleep(rand() % 2);
        printf("WORLD\n");

        pthread_mutex_unlock(&mutex);
        sleep(rand() % 2);
    }
    return NULL;
}


int main(){
    pthread_t tid;

    int ret = pthread_mutex_init(&mutex, NULL);
    if(ret != 0){
        fprintf(stderr, "pthread_mutex_init error: %s\n", strerror(ret));
        exit(1);
    }

    ret = pthread_create(&tid, NULL, tfcn, NULL);
    if(ret != 0){
        fprintf(stderr, "pthread_create error: %s\n", strerror(ret));
        exit(1);
    }
    
    while(1){
        pthread_mutex_lock(&mutex);

        printf("hello ");
        sleep(rand() % 2);
        printf("world\n");
        pthread_mutex_unlock(&mutex);

        sleep(rand() % 2);
    }

    pthread_join(tid, NULL);
    return 0;
}