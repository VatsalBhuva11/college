#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
    fork();
    fork();
    fork();
    printf("Process ID: %d, Parent ID: %d\n", getpid(), getppid());

return 0;
}