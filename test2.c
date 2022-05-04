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
    char* str = "------------------test2 write success------------------\n";
    int ret;

    sleep(3);
    int fd = open("test.txt", O_RDWR | O_APPEND);
    printf("test2 fd is %d\n", fd);

    //尝试读取test.txt的内容
    ret = read(fd, buf, strlen(buf));
    write(STDOUT_FILENO, buf, ret);
    write(fd, str, strlen(str));
    
    printf("test2 write success!\n");

    close(fd);
    return 0;
}