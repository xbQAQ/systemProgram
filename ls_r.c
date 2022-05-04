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

//递归遍历目录
void ls_r(char* path){
    struct stat sb;
    int ret = stat(path, &sb);  
    if(ret < 0){
        perror("stat error!\n");
        exit(1);
    }
    
    //如果是目录，则递归遍历
    if(S_ISDIR(sb.st_mode)){
        DIR* dp = opendir(path);    //打开目录
        if(dp == NULL){
            perror("opendir error!\n");
        }
        struct dirent* pdp;
        while(pdp = readdir(dp)){   //查看目录，pdp对应目录中每一个目录项
            if((strcmp(pdp->d_name, ".") == 0) || (strcmp(pdp->d_name, "..") == 0))
                continue;
            
            if(strlen(path) + strlen(pdp->d_name) + 2 > 256){   //如果当前目录加文件名 + "/" + "\0" > 256，256为绝对路径最长大小
                break;
            }
            
            //char* newpath = (char*)malloc(strlen(path) + strlen(pdp->d_name) + 2);
            //char* newpath;  //未申请空间会发生段错误，没有地方可以存path和pdp->d_name拼接起来的字符串
            char newpath[256];
            sprintf(newpath, "%s/%s", path, pdp->d_name);   //拼接当前目录项的名字和之前目录的名称，保存到newpath，newpath要有自己的内存空间
            
            ls_r(newpath);      //递归遍历目录
            //free(newpath);
        }
        closedir(dp);
    }
    else if(S_ISREG(sb.st_mode)){   //如果是普通文件，则打印
        printf("%s\t%ld\n", path, sb.st_size);
    }
}

int main(int argc, char* argv[]){
    if(argc == 1) ls_r(".");
    else ls_r(argv[1]);
    return 0;
}