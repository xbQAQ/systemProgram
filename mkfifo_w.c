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
    int ret = mkfifo("myfifo", 755);
    if(ret < 0){
        perror("mkfifo error!\n");
        exit(1);
    }
    
    int fd = open("myfifo", O_WRONLY);
    if(fd < 0){
        perror("open fifo error!\n");
        exit(1);
    }

    char buf[1024];
    int i = 0;
    while(1){
        sprintf(buf, "hello myfifo %d\n", i++);
        write(fd, buf, strlen(buf));
        sleep(1);
    }
    return 0;
}