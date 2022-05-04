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
        while(1){
            printf("I'm child, my parent is %d\n", getppid());
            sleep(1);
        }
    }
    else{
        printf("parent process\n");
        sleep(10);
        printf("parent going to die\n");
    }
    return 0;
}