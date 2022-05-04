#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>

void* tfcn(void* arg){
    int i = (int)arg;
    printf("pthread: I'm %d created, my pthread id is %ld\n", i, pthread_self());
    return (void*)(i + 10);
}

int main(){
    pthread_t tid[5];
    int i;
    for(i = 0; i != 5; i++){
        int ret = pthread_create(&tid[i], NULL, tfcn, (void*)(i + 1)); 
        if(ret != 0){
            perror("pthread_create error!\n");
            exit(1);
        }
    }

    int* retval;
    for(i = 0; i != 5; i++){
        pthread_join(tid[i], (void**)&retval);
        if(ret != 0){
            perror("pthread_join error!\n");
            exit(1);
        }
        printf("pthead id %ld has been joined, retval is %d\n", tid[i], (int)retval);
    }
    pthread_exit(0);

    return 0;
}