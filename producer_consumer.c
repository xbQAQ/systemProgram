#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>
#include <sys/types.h>

/*
*   条件变量实现生产者消费者模型
*/

struct Node{
    int val;
    struct Node* next;
};

struct Node* head = NULL;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;  //静态初始化
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* consumer(void* arg){
    int i = (int)arg;
    while(1){
        pthread_mutex_lock(&mutex);
        while(head == NULL){
            pthread_cond_wait(&cond, &mutex);   //头节点为空，那么就进入条件变量进行阻塞等待
        }
        struct Node* p = head;
        head = head->next;
        printf("consumer %d: val is %d\n", i, p->val);
        free(p);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    return NULL;
}

void* producer(void* arg){
    while(1){
        pthread_mutex_lock(&mutex);
        printf("------------producer product!--------------\n");
        struct Node* p = (struct Node*)malloc(sizeof(struct Node));
        p->val = rand() % 10000;
        p->next = head;
        head = p;
        printf("------------producer finish!----------------\n");
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mutex);
        sleep(rand() % 3);
    }
    return NULL;
}

int main(){
    pthread_t p, c[10];
    pthread_attr_t attr;
    int ret = pthread_attr_init(&attr);
    if(ret != 0){
        fprintf(stderr, "pthread_attr_init error: %s\n", strerror(ret));
        exit(1);
    }
    ret = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if(ret != 0){
        fprintf(stderr, "pthread_attr_setdetachstate error: %s\n", strerror(ret));
        exit(1);
    }
    for(int i = 0; i != 10; i++){
    ret = pthread_create(&p, &attr, consumer, (void*)i);
        if(ret != 0){
            fprintf(stderr, "pthread_create error: %s\n", strerror(ret));
            exit(1);
        }
    }
    ret = pthread_create(&p, &attr, producer, NULL);
    if(ret != 0){
        fprintf(stderr, "pthread_create error: %s\n", strerror(ret));
        exit(1);
    }
    ret = pthread_attr_destroy(&attr);
    if(ret != 0){
        fprintf(stderr, "pthread_rwlock_init error: %s\n", strerror(ret));
        exit(1);
    }
    
    pthread_exit(0);
    return 0;
}