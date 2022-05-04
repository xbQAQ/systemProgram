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
#include <sys/mman.h>

int main(){
    int fd = open("mmap.txt", O_CREAT | O_RDWR | O_TRUNC, 644);
    /*
     *  lseek(fd, 20, SEEK_END);    //等同与ftruncate(fd, 20);
     *  write(fd, "\0", 1); 
    */
    ftruncate(fd, 20);  //扩展文件大小
    int len = lseek(fd, 0, SEEK_END);
    char* p = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    strcpy(p, "hello mmap\n");
    printf("%s", p);
    munmap(p, len);
    
    return 0;
}