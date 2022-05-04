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
    pid_t pid = fork();
    if(pid < 0){
        perror("fork error!\n");
        exit(1);
    }
    if(pid > 0){
        printf("---------parent process----------------\n");
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO); //重定向标准输出到管道输出端
        execlp("ls", "ls", NULL);
        pid_t wpid = wait(NULL);
        close(fd[1]);
        printf("---------parent process end------------\n");
    }
    else if(pid == 0){
        printf("---------child process-----------------\n");
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);  //重定向标准输入到管道输出
        execlp("wc", "wc", "-l", NULL);
        close(fd[0]);
        printf("---------child process end-------------\n");
    }
    return 0;
}