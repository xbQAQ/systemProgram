#include <stdio.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

union semun
{
    int val;
    struct semid_ds* buf;
    unsigned short int* array;
    struct seminfo* __buf;
};

void pv(int sem_id, int op){
    struct sembuf sem_buf;
    sem_buf.sem_num = 0;
    sem_buf.sem_op = op;
    sem_buf.sem_flg = SEM_UNDO;
    semop(sem_id, &sem_buf, 1);
}

int main(){
    int sem_id = semget(IPC_PRIVATE, 1, 0666); 

    union semun sem_un;
    sem_un.val = 1;
    semctl(sem_id, 0, SETVAL, sem_un);

    pid_t pid = fork();
    if(pid < 0){
        return 1;
    }
    else if(pid == 0){
        printf("child try to get binary sem\n");
        /*在父子进程间共享IPC_PRIVATE的关键就在于两者都可以操作该信号量的标识符sem_id*/
        pv(sem_id, -1);
        printf("child try to get binary sem and release sem after 5 seconds\n");
        sleep(5);
        pv(sem_id, 1);
        exit(0);
    }
    else{
        printf("parent try to get binary sem\n");
        pv(sem_id, -1);
        printf("parent try to get binary sem and release sem after 5 seconds\n");
        sleep(5);
        pv(sem_id, 1);
    }
    waitpid(pid, NULL, 0);
    semctl(sem_id, 0, IPC_RMID, sem_un);
    return 0; 
}