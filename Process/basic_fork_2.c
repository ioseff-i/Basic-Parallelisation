#include<stdio.h>
#include<unistd.h>
int main(){
    printf("INITIAL PROCESS with PID: %d\n", getpid());
    pid_t pid = fork();
    if(pid > 0){
        printf("This is the parent process with PID: %d\n",getpid());
        printf("The value of pid in parent process: %d\n",pid);
    }
    else if(pid == 0){
        printf("This is the child process with PID: %d\n",getpid());
        printf("The value of pid in child process: %d\n",pid);
    }
    else{
        printf("Fork failed\n");
    }
}