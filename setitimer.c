#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    struct itimerval curval, oldval;
    curval.it_value.tv_sec = 1;
    curval.it_value.tv_usec = 0;
    curval.it_interval.tv_sec = 0;
    curval.it_interval.tv_usec = 0;

    int res = setitimer(ITIMER_REAL, &curval, &oldval);
    if(res < 0){
        perror("setitimer error!\n");
        exit(1);
    }
    
    int i = 0;
    while(1){
        printf("%d\n", ++i);
    }
    return 0;
}