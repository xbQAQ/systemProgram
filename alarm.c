#include <stdio.h>
#include <unistd.h>

int main(){
    int i = 0;
    alarm(1);
    while(1){
        printf("%d\n", ++i);
    }
    return 0;
}