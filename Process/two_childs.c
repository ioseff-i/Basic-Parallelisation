#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int job_sum(int n){
    int sum = 0;
    for(int i = 0; i < n; i++){
        sum += i;
    }
    return sum;
}
int job_product(int n){
    int product = 1;
    for(int i = 1; i <= n; i++){
        product *= i;
    }
    return product;
}
int job_difference(int a, int b){
    return a - b;
}

int main(){
    pid_t pid1 = fork();
    if(pid1 > 0){
        printf("Parent process with PID: %d is executing...\n", getpid());
        printf("The value of the pid is: %d\n", pid1);
        int status_of_first_child;
        wait(&status_of_first_child);
        status_of_first_child = WEXITSTATUS(status_of_first_child);
        if (status_of_first_child == 0){
            printf("First child process performed successfully (result_sum was 45).\n");
        }
        else if (status_of_first_child == 1){
            printf("First child process performed unsuccessfully (result_sum was not 45).\n");
        }
        else{
            printf("First child process exited with an unexpected status: %d\n", status_of_first_child);
        }
        int result_product = job_product(5);
        printf("Result of job_product in parent process: %d\n", result_product);
        printf("Parent process is done.\n");
    }
    else if(pid1==0){
        printf("First child process with PID: %d is executing...\n", getpid());
        printf("The value of the pid is: %d\n", pid1);
        pid_t pid2 = fork();
        if (pid2>0){
            printf("First child process with PID: %d created a second child process with PID: %d\n", getpid(), pid2);
            int status_of_second_child;
            wait(&status_of_second_child);
            status_of_second_child = WEXITSTATUS(status_of_second_child);
            if (status_of_second_child == 0){
                printf("Second child process performed successfully (result_difference was 5).\n");
            }
            else if (status_of_second_child == 1){
                printf("Second child process performed unsuccessfully (result_difference was not 5).\n");
            }
            else{
                printf("Second child process exited with an unexpected status: %d\n", status_of_second_child);
            }
            int result_sum = job_sum(10);
            if (result_sum == 45){
                exit(0);
            }
            else{
                exit(1);
            }
        }
        else if(pid2 == 0){
            printf("Second child process with PID: %d is executing...\n", getpid());
            printf("The value of the pid is: %d\n", pid2);
            int difference = job_difference(10, 5);
            if(difference == 5){
                exit(0);
            }
            else{
                exit(1);
            }
        }
        else{
            printf("Fork failed\n");
        }

    }
    else{
        printf("Fork failed\n");
    }







    return 0;
}