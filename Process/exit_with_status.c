#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
int job1(){
    int sum = 0;
    for(int i = 0; i < 100; i++){
        sum += i;
    }
    return sum;
}
int job2(){
    int product = 1;
    for(int i = 1; i <= 5; i++){
        product *= i;
    }
    return product;
}
int main(){
    pid_t pid = fork();
    if(pid > 0){
        printf("Parent process with PID: %d is executing job1...\n", getpid());
        int result1 = job1();
        printf("Result of job1 in parent process: %d\n", result1);
        
        // Parent process can also check the exit status of the child process
        int status;
        wait(&status);
        status = WEXITSTATUS(status);
        if (status == 1){
            printf("Child status performed successfully (result2 was 120).\n");
        }
        else if (status == 0){
            printf("Child status performed unsuccessfully (result2 was not 120).\n");
        }
        else{
            printf("Child process exited with an unexpected status: %d\n", status);
        }
        printf("Parent process is done.\n");

    }
    else if(pid == 0){
        printf("Child process with PID: %d is executing job2...\n", getpid());
        int result2 = job2();
        printf("Result of job2 in child process: %d\n", result2);
        printf("Child process is done.\n");

        if(result2 == 120){
            exit(1);
        }
        else{
            exit(0);
        }
    }
    else{
        printf("Fork failed\n");
    }



    return 0;
}