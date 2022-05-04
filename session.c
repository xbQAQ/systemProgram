#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    pid_t pid;
    pid = fork();
    if(pid < 0){
        perror("fork error!\n");
        exit(1);
    }

    if(pid == 0){
        printf("%d\t%d\t%d\n", getpid(), getpgid(0), getsid(0));
        sleep(10);
        setsid();
        printf("change!\n");
        printf("%d\t%d\t%d\n", getpid(), getpgid(0), getsid(0));
        sleep(10);
    }
    else{
        sleep(5);
    }
    
    
    return 0;
}