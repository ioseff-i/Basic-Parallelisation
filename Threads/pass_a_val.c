#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
void*job(void*arg){
    int* value = (int*)arg;
    printf("The value passed to the thread is: %d\n", *value);
    free(value); // Free the allocated memory
    return NULL;
}

int main(){

    // pthread_t t1, t2, t3;
    int num_threads;
    scanf("%d", &num_threads);


    pthread_t* threads = (pthread_t*)malloc(num_threads * sizeof(pthread_t));

    for(int i = 0; i < num_threads; i++){
        int* val = malloc(sizeof(int));
        *val = i + 1; // Assign a unique value to each thread
        pthread_create(&threads[i], NULL, job, val);
        free(val); 
    }
    

    for(int i = 0; i < num_threads; i++){
        pthread_join(threads[i], NULL);
    }



    // int val1 = 10, val2 = 20, val3 = 30;

    // pthread_create(&t1,NULL,job,&val1);
    // pthread_create(&t2,NULL,job,&val2);
    // pthread_create(&t3,NULL,job,&val3);

    // pthread_join(t1,NULL);
    // pthread_join(t2,NULL);
    // pthread_join(t3,NULL);

    printf("All threads have finished their job!\n");
    free(threads); // Free the allocated memory for thread IDs
    return 0;
}