#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
void* job_func(void* arg){
    int*num = (int*)arg;
    printf("Thread processing number: %d\n", *num);
    *num = *num * *num;
    return (void*)(num);
}


void* job_func2(void* arg){
    int* num = (int*)arg;
    printf("Thread processing number: %d\n", *num);
    char* str = (char*)malloc(20*sizeof(char));
    sprintf(str, "Number: %d", *num * *num);
    sleep((*num));
    printf("Thread created string: %s\n", str);
    // sleep(50000); // Simulate some work
    // *num = *num * *num;
    return (void*)(str);
}

int main(){
    int num_threads;
    scanf("%d",&num_threads);
    pthread_t* t = (pthread_t*)malloc(num_threads*sizeof(pthread_t));

    for(int i = 0; i < num_threads; i++){
        int* num = (int*)malloc(sizeof(int));
        *num = i;
        pthread_create(&t[i], NULL, job_func2, num);
    }

    for(int i = 0; i < num_threads; i++){
        void* result;
        pthread_join(t[i], &result);
        printf("Thread %d returned: %s\n", i, (char*)result);
        free(result); // Free the allocated memory for the result
    }

    free(t);
    return 0;
}