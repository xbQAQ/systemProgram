#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>
#include <sys/types.h>
#include <semaphore.h>

/*
*   信号量实现生产者消费者模型
*/

#define MAX_NUM 5

sem_t consumerSem, producerSem;
int arr[MAX_NUM] = {0};

void* consumer(void* arg){
    int i = 0;
    while(1){
        sem_wait(&consumerSem);      //产品数--
        printf("consumer: value is %d\n", arr[i]);
        arr[i] = 0;
        sem_post(&producerSem);         //空格数++
        i = (i + 1) % MAX_NUM;
        sleep(rand() % 3);
    }
    return NULL;
}

void* producer(void* arg){
    int i = 0;
    while(1){
        sem_wait(&producerSem);     //产品数++
        arr[i] = rand() % 1000 + 1;
        printf("----------produce produce value is %d---------\n", arr[i]);
        sem_post(&consumerSem);
        i = (i + 1) % MAX_NUM;
        sleep(rand() % 1);
    }
    return NULL;
}

int main(){
    int ret = sem_init(&producerSem, 0, MAX_NUM);       //生产者信号量，表示队列里有无空余
    if(ret < 0){
        perror("sem_init error!\n");
        exit(1);
    }
    ret = sem_init(&consumerSem, 0, 0);                 //消费者信号量，表示队列里有无数据
    if(ret < 0){
        perror("sem_init error!\n");
        exit(1);
    }

    pthread_t cid, pid;
    pthread_attr_t attr;
    ret = pthread_attr_init(&attr);     //初始化属性
    if(ret != 0){
        fprintf(stderr, "pthread_attr_init error: %s\n", strerror(ret));
        exit(1);
    }
    ret = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);  //设置分离属性
    if(ret != 0){
        fprintf(stderr, "pthread_attr_setdetachstate error: %s\n", strerror(ret));
        exit(1);
    }
    ret = pthread_create(&cid, &attr, consumer, NULL);
    if(ret != 0){
        fprintf(stderr, "pthread_create error: %s\n", strerror(ret));
        exit(1);
    }
    ret = pthread_create(&pid, &attr, producer, NULL);
    if(ret != 0){
        fprintf(stderr, "pthread_create error: %s\n", strerror(ret));
        exit(1);
    }
    ret = pthread_attr_destroy(&attr);  //销毁属性
    if(ret != 0){
        fprintf(stderr, "pthread_rwlock_init error: %s\n", strerror(ret));
        exit(1);
    }

    ret = sem_destroy(&producerSem);
    if(ret < 0){
        perror("sem_init error!\n");
        exit(1);
    }
    ret = sem_destroy(&consumerSem);
    if(ret < 0){
        perror("sem_init error!\n");
        exit(1);
    }

    pthread_exit(0);

    return 0;
}