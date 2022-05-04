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
        int fd = open("psaux.txt", O_CREAT | O_APPEND | O_RDWR);
        dup2(fd, STDOUT_FILENO);
        execlp("ps", "ps", "-aux", NULL);
    }
    else{
        printf("parent process!\n");
    }
    return 0;
}