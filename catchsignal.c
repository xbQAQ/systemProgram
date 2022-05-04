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
    signal(SIGINT, catchSignal);
    while(1);
    return 0;
}
