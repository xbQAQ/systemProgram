#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

void func(){
    static int i = 0;
    printf("time: %ld, value is %d\n", clock() / 1000000, ++i);
}

int main(){
    struct itimerval curval, oldval;
    curval.it_value.tv_sec = 1;
    curval.it_value.tv_usec = 0;
    curval.it_interval.tv_sec = 5;
    curval.it_interval.tv_usec = 0;

    int res = setitimer(ITIMER_REAL, &curval, &oldval);
    if(res < 0){
        perror("setitimer error!\n");
        exit(1);
    }

    signal(SIGALRM, func);
    while(1){
        
    }
    return 0;
}