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
    int* p;
    pid_t pid;

    int fd = open("temp", O_RDWR);
    if(fd < 0){
        perror("open error!\n");
        exit(1);
    }

    int ret = ftruncate(fd, 4);
    if(ret < 0){
        perror("ftruncate error!\n");
        exit(1);
    }
    int len = lseek(fd, 0, SEEK_END);
    p = (int*)mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);   
    if(p == MAP_FAILED){
        perror("mmap error!\n");
        exit(1);
    }
    //MAP_SHARED表示1. 修改映射的内存时也会修改磁盘，2.映射的更新对于映射同一区域的其他进程也是可见的
    //MAP_PRIVATE表示1. 修改映射的内存时不会修改磁盘，2.映射的更新对于映射同一区域的其他进程是不可见的
    //p = (int*)mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);

    //*p = 100;
    printf("2. p's address is %p, value is %d\n", p, *p);
    *p = 200;
    printf("2. p's address is %p, value is %d\n", p, *p);

    close(fd);
    munmap(p, len);

    return 0;
}