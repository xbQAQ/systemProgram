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
    int fd = open("myfifo", O_RDONLY);
    char buf[1024];
    while(1){
        read(fd, buf, strlen(buf));
        write(STDOUT_FILENO, buf, strlen(buf));
        sleep(3);
    }
    return 0;
}