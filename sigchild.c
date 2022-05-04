#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/signal.h>

void waitchild(int signum){
    pid_t wpid;
    int status;
    while((wpid = waitpid(-1, &status, WNOHANG)) >= 0){
        if(WIFEXITED(status)){
            printf("child pid is %d, return value is %d\n", wpid, WEXITSTATUS(status));
        }
        if(wpid == 0){
            printf("child pid %d has stoped, signal number is %d\n", wpid, signum);
            break;
        }
    }
    return;
}

int main(){
    pid_t pid;
    int i;
    //阻塞信号
    sigset_t sig, oldsig;
    sigemptyset(&sig);
    sigaddset(&sig, SIGCHLD);
    sigprocmask(SIG_BLOCK, &sig, &oldsig);
    
    for(i = 0; i != 5; i++){
        if((pid = fork()) == 0)
            break;
    }

    if(i == 5){
        printf("\n");
        struct sigaction act, oldact;
        act.sa_handler = waitchild;
        sigemptyset(&act.sa_mask);
        act.sa_flags = 0;
        sigaction(SIGCHLD, &act, &oldact);  //注册信号捕捉函数
        sigprocmask(SIG_UNBLOCK, &sig, &oldsig);    //如果不解除阻塞，那么信号会处于未决态，解除阻塞之后，信号会递达，执行处理动作

        kill(getpid() + 1, SIGSTOP);
        while(1){
            char buf[10];
            scanf("%s", buf);
            printf("%s\n", buf);
        }
    }
    else{
        printf("child pid is %d\n", getpid());
        sleep(i);
    }
    return 0;
}