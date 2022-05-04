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
    char* p;
    int fd = open("mmap.txt", O_RDWR);
    if(fd == -1){
        perror("open error!\n");
        exit(1);
    }
    //int fd = open("mmap.txt", O_CREAT | O_RDONLY | O_TRUNC, 644);
    /*
     *  lseek(fd, 20, SEEK_END);    //等同与ftruncate(fd, 20);
     *  write(fd, "\0", 1); 
    */
    ftruncate(fd, 40000);  //扩展文件大小, 只读情况下不能拓展
    int len = lseek(fd, 0, SEEK_END);
    printf("%d\n", len);

    //文件大小为0, mmap长度为>0, 无效参数
    //文件大小为>0, mmap长度为0, 无效参数
    //文件读写，mmap只写，没错
    //文件读写，mmap只读, 段错误
    //文件只读，mmap只读, 段错误
    //文件只写，mmap只写，权限错误
    //文件只读, mmap读写，权限错误
    //文件只写, mmap读写, 权限错误
    //mmap需要文件读权限，且mmap权限要小于等于文件权限
    //mmap偏移量必须是4k(4096Byte)的整数倍, 与MMU有关，MMU映射的最小单位为4k
    //映射区访问权限为MAP_PRIVATE, 对内存所做所有操作只对内存有效, 不会映射到磁盘上 
    p = mmap(NULL, len, PROT_WRITE, MAP_SHARED, fd, 0);
    //匿名共享映射，MAP_ANONYMOUS或者MAP_ANON
    //p = mmap(NULL, len, PROT_WRITE | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if(p == MAP_FAILED){
        perror("mmap error!\n");
        exit(1);
    }
    strcpy(p, "hello mmap\n");
    printf("%s", p);
    munmap(p, len);
    
    return 0;
}