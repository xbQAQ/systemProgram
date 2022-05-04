#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

void catchSignal(int signo){
    printf("catch you %d!\n", signo);
    return;
}

int main(){
    struct sigaction act, oldact;
    act.sa_handler = catchSignal;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    int ret = sigaction(SIGINT, &act, &oldact);
    if(ret < 0){
        perror("sigaction error!\n");
        exit(1);
    }
    while(1);
    return 0;
}