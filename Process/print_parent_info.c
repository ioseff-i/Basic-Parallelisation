#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){
    printf("Main process has been started before the forking...\n");
    pid_t pid = fork();
    if(pid>0){
        printf("This is the parent process with PID: %d\n",getpid());
        printf("The value of pid in parent process: %d\n",pid);
        printf("The parent id of the parent process is: %d\n",getppid());
        // sleep(20);
        printf("Parent process is done.\n");
        wait(NULL);
        printf("Child process has been finished as well!\n");
    }
    else if(pid == 0){
        printf("The process id of the child process is:%d\n",getpid());
        printf("Pid Value here is: %d\n",pid);
        printf("The parent id of the child process is: %d\n",getppid());

    }
    else{
        printf("Fork failed\n");

    }
}