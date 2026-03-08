#include<stdio.h>
#include<unistd.h>
int main(){
    printf("Before the fork process with PID: %d\n", getpid());
    fork();
    printf("After the fork process with PID: %d\n", getpid());
    return 0;
}