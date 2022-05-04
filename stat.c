#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

int main(int argc, char** argv){
    char* filename = argv[1];
    struct stat sb;
    int ret = stat(filename, &sb);
    if(ret < 0){
        perror("stat\n");
        exit(1);
    }
    printf("%d\n" ,S_ISDIR(sb.st_mode));
    return 0;
}