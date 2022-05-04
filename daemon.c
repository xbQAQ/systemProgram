#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(){
    pid_t pid;
    pid = fork();
    if(pid < 0){
        perror("fork error!\n");
        exit(1);
    }
    
    if(pid > 0){
        exit(1);
    }
    else{
        pid = setsid();
        if(pid == -1){
            perror("setsid error!\n");
            exit(1);
        }

        int ret = chdir("/");
        if(ret < 0){
            perror("chdir error!\n");
            exit(1);
        }

        umask(0022);

        close(STDIN_FILENO);
        int fd = open("/dev/null", O_RDWR); //fd == 0
        if(fd < 0){
            perror("open error!\n");
            exit(1);
        }
        dup2(fd, STDIN_FILENO);
        dup2(fd, STDOUT_FILENO);
        dup2(fd, STDERR_FILENO);

        while(1){
            printf("daemon!\n");
            sleep(5);
        }
    }
    return 0;
}