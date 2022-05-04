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

int main(int argc, char* argv[]){
    printf("-------------before fork1--------------\n");
    printf("-------------before fork2--------------\n");
    printf("-------------before fork3--------------\n");
    printf("-------------before fork4--------------\n");
    pid_t pid = fork();
    if(pid < 0){
        perror("fork error!\n");
        exit(1);
    }
    else if(pid == 0){
        printf("child create\n");
        printf("child pid is %d, child's ppid is %d\n", getpid(), getppid());
    }
    else{
        printf("parent process: my child is %d\n", pid);
        printf("parent pid is %d, parent's parent ppid is %d\n", getpid(), getppid());
    }

    printf("--------------after fork1--------------------\n");
    printf("--------------after fork2--------------------\n");
    printf("--------------after fork3--------------------\n");
    printf("--------------after fork4--------------------\n");
    sleep(100);
    return 0;
}