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
        int status;
        // pid_t wpid = wait(&status); //阻塞等待，直到有子进程死亡，随机选择一个回收
        //waitpid:
        //选择特定pid回收
        //参数2，
        //<-1表示回收特定进程组的任何一个子进程
        //-1 表示回收任意一个子进程
        //0  表示回收进程组gid等于父进程的进程组gid
        //>0 表示回收特定子进程
        //参3，0表示默认阻塞等待，WNOHANG表示不阻塞，如果参3使用WNOHANG，则如果没有回收到子进程，则返回0
        printf("tpid is %d\n", tpid);
        pid_t wpid = waitpid(tpid, &status, 0);      
        if(WIFEXITED(status)){
            printf("child return status is %d\n", WEXITSTATUS(status));
        }
        if(WIFSIGNALED(status)){
            printf("killed by signal %d\n", WTERMSIG(status));
        }
        printf("wpid is: %d\n", wpid);
    }
    else{
        sleep(10);
        printf("I'm %dth child, my pid is %d\n", i + 1, getpid());
        return 95;
    }

    return 0;
}