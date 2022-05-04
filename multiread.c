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
        write(fd[1], "hello fork1\n", sizeof("hello fork1\n"));
    }
    else if(i == 1){
        printf("my pid is %d\n", getpid());
        close(fd[0]);
        write(fd[1], "hello fork2\n", sizeof("hello fork2\n"));
    }
    else if(i == 2){
        close(fd[1]);
        
        char buf[1024] = {"0"};
        
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

        read(fd[0], buf, 1024);
        write(STDOUT_FILENO, buf, sizeof(buf));
    }

    return 0;
}