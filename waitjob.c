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
#include <sys/wait.h>
#include <fcntl.h>

int main(){
    pid_t pid, wpid;
    pid_t pidarray[3];
    int i;
    for(i = 0; i != 3; i++){
        pid = fork();
        if(pid == 0) {
            pidarray[i] = getpid();
            break;
        }
    }

    if(i == 3){
        while((wpid = waitpid(-1, NULL, WNOHANG)) != -1){
            if(wpid > 0){
                printf("%d child has been wait\n", wpid);
            }
        }
    }
    else{
        printf("-------------------------------child process------------------------------------\n");
        printf("mypid is %d\n", getpid());
        if(getpid() == pidarray[0]){
            int id = open("psLog.txt", O_CREAT | O_APPEND | O_RDWR, 644);
            dup2(id, STDOUT_FILENO);
            execlp("ps", "ps", "-aux", NULL);
            sleep(1);
        }
        else if(getpid() == pidarray[1]){
            execl("./ls_r", "ls_r", NULL);
            sleep(1);
        }
        else if(getpid() == pidarray[2]){
            execl("./segfalut", "segfalut", NULL);
            sleep(1);
        }
    }
    return 0;
}