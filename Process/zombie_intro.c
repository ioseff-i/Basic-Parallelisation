#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    pid_t pid = fork();

    if(pid > 0){
        // parent sleeps 30 seconds WITHOUT calling wait()
        printf("Parent PID: %d, child PID: %d\n", getpid(), pid);
        sleep(10);
        printf("Parent done.\n");
        wait(NULL);
        printf("Child process has been finished as well!");

    }
    else if(pid == 0){
        // child sleeps 5 seconds then dies
        printf("Child PID: %d working...\n", getpid());
        sleep(5);
        printf("Child finished.\n");
        // child exits here
        // parent still sleeping for 25 more seconds
        // zombie window: 25 seconds!
    }
}