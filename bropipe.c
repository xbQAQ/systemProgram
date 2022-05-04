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
    int fd[2];
    int ret = pipe(fd);
    if(ret < 0){
        perror("pipe error!\n");
        exit(1);
    }
    pid_t pid;
    int i;
    for(i = 0; i != 2; i++){
        if((pid = fork()) == 0){
            break;
        }
        if(pid < 0){
            perror("fork error!\n");
            exit(1);
        }
    }

    if(i == 0){
        printf("my pid is %d\n", getpid());
        close(fd[0]);
        int ret = dup2(fd[1], STDOUT_FILENO);
        if(ret < 0){
            perror("dup2 error!\n");
        }
        execlp("ls", "ls", NULL);
    }
    else if(i == 1){
        printf("my pid is %d\n", getpid());
        close(fd[1]);
        int ret = dup2(fd[0], STDIN_FILENO);
        if(ret < 0){
            perror("dup2 error!\n");
        }
        execlp("wc", "wc", "-l", NULL);
    }
    else if(i == 2){
        close(fd[0]);
        close(fd[1]);
        pid_t wpid;
        int status;
        //回收子进程
        while((wpid = wait(&status)) != -1){
            printf("child %d has been reclaim\n", wpid);
            if(WIFEXITED(status)){
                printf("return value is %d\n", WEXITSTATUS(status));
            }
            else if(WIFSIGNALED(status)){
                printf("kill by %d", WTERMSIG(status));
            }
        }
    }

    return 0;
}