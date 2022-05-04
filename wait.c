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

int main(int argc, char* argv[]){
    int i;
    pid_t pid, tpid;

    for(i = 0; i != 5; i++){
        if((pid = fork()) == 0)
            break;
        if(i == 2)
            tpid = pid;
    }
    if(i == 5){
        sleep(12);
        int status;
        pid_t wpid = wait(&status); //阻塞等待，直到有子进程死亡，随机选择一个回收
        // pid_t wpid = waitpid(tpid, &status, 0);      //参3，0表示默认阻塞等待，WNOHANG表示不阻塞，如果参3使用WNOHANG，则如果没有回收到子进程，则返回0
        if(WIFEXITED(status)){
            printf("child return status is %d\n", WEXITSTATUS(status));
        }
        if(WIFSIGNALED(status)){
            printf("killed by signal %d\n", WTERMSIG(status));
        }
        printf("wpid is: %d\n", wpid);
    }
    else{
        sleep(1);
        printf("I'm %dth child, my pid is %d\n", i + 1, getpid());
        return 25;
    }

    return 0;
}