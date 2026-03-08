#include<stdio.h>
#include<unistd.h>

int main(){
    printf("This is the main process with PID: %d\n", getpid());
    return 0;
}