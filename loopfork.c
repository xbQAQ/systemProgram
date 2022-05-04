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

int main(int argc, char* argv[]){
    int i;
    pid_t pid;

    for(i = 0; i != 5; i++){
        if(fork() == 0)
            break;
    }
    if(i == 5){
        sleep(1);
        printf("I'm parent\n");
    }
    else{
        sleep(i);
        printf("I'm %dth child\n", i + 1);
    }

    return 0;
}