#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char buf[10];
    int fd, n;

    fd = open("/dev/tty", O_RDONLY | O_NONBLOCK);
    if(fd < 0){
        perror("open /dev/tty");
        exit(1);
    }

    while(1){
        n = read(fd, buf, 10);
        if(n < 0){
            if(errno != EAGAIN || errno != EWOULDBLOCK){
                perror("read /dev/tty");
                exit(1);
            }
            else{
                write(STDOUT_FILENO, "try again\n", strlen("try again\n"));
                sleep(2);
            }
        }
        else{
            break;
        }
    }

    write(STDOUT_FILENO, buf, n);
    close(fd);

    return 0;
}