#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>

pthread_rwlock_t rwlock;
int value;

void* rdThread(void* arg){
    int i = (int)arg;
    printf("------rdThread-------\n");
    while(1){
        sleep(rand() % 1);
        pthread_rwlock_rdlock(&rwlock);
        printf("rdThread %d: value is: %d\n", i, value);
        pthread_rwlock_unlock(&rwlock);
        sleep(rand() % 2);
    }
    printf("------rdThread-------\n");
    return NULL;
}

void* wrThread(void* arg){
    int i = (int)arg;
    printf("------wrThread-------\n");
    int t;
    while(1){
        sleep(1);
        pthread_rwlock_wrlock(&rwlock);
        t = value;
        usleep(20);
        printf("----------------wrThread %d: value is: %d, ++value is: %d\n", i, t, ++value);
        pthread_rwlock_unlock(&rwlock);
        sleep(rand() % 3);
    }
    printf("------wrThread-------\n");
    return NULL;
}

int main(){
    value = 0;
    int ret = pthread_rwlock_init(&rwlock, NULL);
    if(ret != 0){
        fprintf(stderr, "pthread_rwlock_init error: %s\n", strerror(ret));
        exit(1);
    }
    pthread_t tid[1500];

    pthread_attr_t attr;
    ret = pthread_attr_init(&attr);
    if(ret != 0){
        fprintf(stderr, "pthread_attr_init error: %s\n", strerror(ret));
        exit(1);
    }
    ret = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if(ret != 0){
        fprintf(stderr, "pthread_attr_setdetachstate error: %s\n", strerror(ret));
        exit(1);
    }

    for(int i = 0; i != 1000; i++){
        ret = pthread_create(&tid[i], &attr, rdThread, (void*)i);
        if(ret != 0){
            fprintf(stderr, "pthread_create error: %s\n", strerror(ret));
            exit(1);
        }
    }
    for(int i = 1000; i != 1500; i++){
        ret = pthread_create(&tid[i], &attr, wrThread, (void*)i);
        if(ret != 0){
            fprintf(stderr, "pthread_create error: %s\n", strerror(ret));
            exit(1);
        }
    }

    ret = pthread_attr_destroy(&attr);
    if(ret != 0){
        fprintf(stderr, "pthread_attr_destroy error: %s\n", strerror(ret));
        exit(1);
    }
    
    ret = pthread_rwlock_destroy(&rwlock);    
    if(ret != 0){
        fprintf(stderr, "pthread_rwlock_destroy error: %s\n", strerror(ret));
        exit(1);
    }

    pthread_exit(0);

    return 0;
}