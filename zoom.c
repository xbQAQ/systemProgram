#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <dirent.h>

int main(){
    pid_t pid = fork();
    if(pid < 0){
        perror("fork error!\n");
        exit(1);
    }
    else if(pid == 0){
        printf("child process\n");
        sleep(10);
        printf("child going to die\n");
    }
    else{
        while(1){
            printf("I'm parent, pid is %d, my child is %d\n", getpid(), pid);
            sleep(1);
        }
    }
    return 0;
}