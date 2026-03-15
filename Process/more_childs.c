#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int job_one(){
    int sum = 0;
    for(int i = 0; i < 10; i++){
        sum += i;
    }
    return sum;
}
int job_two(){
    int product = 1;
    for(int i = 1; i <= 5; i++){
        product *= i;
    }
    return product;
}
int job_three(){
    int difference = 100;
    for(int i = 1; i <= 10; i++){
        difference -= i;
    }
    return difference;
}
int main(){
    pid_t pids[3];   // store all child PIDs

    // CREATE LOOP - just spawn, don't wait
    for(int i = 0; i < 3; i++){
        pids[i] = fork();

        if(pids[i] == 0){
            sleep(rand() % 3);
            // CHILD
            printf("Child %d with PID:%d starting...\n", i, getpid());
            // sleep(1);
            int result;
            if(i == 0) {
                result = job_one();
                if (result == 45){
                    exit(0);   // success
                }
                else{
                    exit(1);   // failure
                }

            }
            else if(i == 1) {
                result = job_two();
                if (result == 120){
                    exit(0);   // success
                }
                else{
                    exit(1);   // failure
                }
            }
            else {
                result = job_three();

                if (result == 45){
                    exit(0);   // success
                }
                else{
                    exit(1);   // failure
                }
            }
            // exit(i);   // exit with child number as code
        }
        else if(pids[i] < 0){
            printf("Fork failed\n");
            exit(1);
        }
        // parent does NOT wait here - just loops and creates next child
    }

    // WAIT LOOP - collect all children
    for(int i = 0; i < 3; i++){

        int status;
        int child_number = -1;  // initialize to an invalid value
        pid_t child_code = wait(&status);
        for (int j = 0; j < 3; j++){
            if (child_code == pids[j]){
                child_number = j;
            }
        }


        int code = WEXITSTATUS(status);

        if (code == 0){
            printf("Child %d performed successfully.\n", child_number);
        }
        else if (code == 1){
            printf("Child %d performed unsuccessfully.\n", child_number);
        }
        else{
            printf("Child %d exited with an unexpected status: %d\n", child_number, code);
        }
    }

    printf("Parent done. All children finished.\n");
    return 0;
}