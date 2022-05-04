#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/wait.h>

int main(){
    pid_t pid, wpid;
    int status;
    int i;
    for(i = 0; i != 5; i++){
        pid = fork();
        if(pid == 0) break;
    }
    if(i == 5){
        while((wpid = waitpid(-1, &status, WNOHANG)) != -1){
            if(wpid > 0){
                printf("It have'n wait child, the pid is %d\n", wpid);
            }
            else if(wpid == 0){
                sleep(1);
                printf("child still running\n");
            }
        }
    }
    else{
        sleep(1);
        printf("my pid is %d, my parent is %d\n", getpid(), getppid());
    }
    return 0;
}