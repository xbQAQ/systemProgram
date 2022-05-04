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
    char buf[1024];
    char* str = "-------------------success--------------------\n";
    int ret;

    int fd = open("test.txt", O_RDWR | O_TRUNC | O_CREAT, 644);
    printf("test1 fd is %d\n", fd);

    write(fd, str, strlen(str));
    printf("test1 write into test.txt finish\n");

    sleep(10);
    
    lseek(fd, 0, SEEK_SET);
    ret = read(fd, buf, sizeof(buf));
    ret = write(STDOUT_FILENO, buf, ret);

    if(ret == -1){
        perror("write second error!\n");
        exit(1);
    }

    close(fd);

    return 0;
}