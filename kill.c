#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(){
    pid_t pid, tpid;
    int i;
    int fd[2];
    int ret = pipe(fd);
    if(ret < 0){
        perror("pipe error!\n");
        exit(1);
    }

    for(i = 0; i != 5; i++){
        pid = fork();
        if(pid == 0){
            break;
        }
    }    
    
    if(i == 5){
        sleep(5);
        char buf[10];
        int status;
        ret = read(fd[0], buf, sizeof(buf));
        pid_t cpid = atoi(buf);
        printf("parent %d\n", cpid);
        if(ret < 0){
            perror("read error!\n");
            exit(1);
        }
        while((waitpid(cpid, &status, WNOHANG) == 0)){
            ret = kill(cpid, SIGKILL);
            if(ret < 0){
                perror("kill error!\n");
                exit(1);
            }
            if(WIFSIGNALED(status)){
                printf("%d\n", WTERMSIG(status));
            }
        }

        close(fd[1]);
        while(1);
    }
    else{
        if(i == 3){
            close(fd[0]);
            pid_t mpid = getpid();
            char buf[10];
            sprintf(buf, "%d", mpid);
            printf("child %d\n", mpid);
            write(fd[1], buf, sizeof(buf));
            close(fd[1]);
            while(1);
        }
        while(1);
    }
    return 0;
}