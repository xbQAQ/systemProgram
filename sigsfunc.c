#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

void print_set(sigset_t* set){
    int i;

    for(i = 1; i < 32; i++){
        if(sigismember(set, i))
            putchar('1');
        else 
            putchar('0');
    }
    printf("\n");
}

int main(){
    sigset_t set, oldset, pedset;

    int ret = 0;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    sigaddset(&set, SIGQUIT);

    ret = sigprocmask(SIG_BLOCK, &set, &oldset);
    if(ret == -1){
        perror("sigprocmask error!\n");
        exit(1);
    }

    while(1){
        ret = sigpending(&pedset);
        if(ret == -1){
            perror("sigpending error!\n");
            exit(1);
        }
        print_set(&pedset);
        sleep(1);
    }
    return 0;
}