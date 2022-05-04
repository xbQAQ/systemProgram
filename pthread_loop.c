#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>

void* tfunc(void* arg){
    int i = (int)arg;
    printf("thread: I'm %d created, my pthread id is %ld,  pid is %d\n", i, pthread_self(), getpid());
}

int main(){
    pthread_t tid;
    pid_t pid;
    int i;

    for(i = 0; i != 5; i++){
        int ret = pthread_create(&tid, NULL, tfunc, (void*)i);
        if(ret < 0){
            perror("pthread error!\n");
            exit(1);
        }
    }

    printf("Main: my pthread id is %ld, pid is %d\n", pthread_self(), getpid());

    pthread_exit(NULL);
    return 0;
}