#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
#include<math.h>

#define MAX_EL 1000
#define MAX_THREADS 4

long long int array1[MAX_EL];
long long int array2[MAX_EL];
long long int array3[MAX_EL];
long long int array4[MAX_EL];

typedef struct{
    int thread_id;
    long long int *array;
    int size;
    long long int sum;
}thread_item;

void assign_array(){
    for(int i = 0; i < MAX_EL; i++){
        array1[i] = (long long int)pow(i, 2);
        array2[i] = (long long int)pow(i, 3);
        array3[i] = (long long int)pow(i, 4);
        array4[i] = (long long int)pow(i, 5);
    }
    return;
}

void* sum_array(void* arg){
    thread_item* item = (thread_item*) arg;

    long long int sum = 0;
    for(int i = 0; i < MAX_EL; i++){
        sum += item -> array[i];
    }
    item -> sum = sum;

    printf("Thread %d: Sum = %lld\n", item -> thread_id, item -> sum);
    pthread_exit(NULL);
}

int main(){
    assign_array();

    clock_t start, end;
    start = clock();
    long long int* independent_arrays[4] = {array1, array2, array3, array4};
    pthread_t threads[MAX_THREADS];
    thread_item thread_items[MAX_THREADS];

    for(int i = 0; i < MAX_THREADS; i++){
        thread_items[i].thread_id = 1;
        thread_items[i].array = independent_arrays[i];
        thread_items[i].size = MAX_EL;
        if(pthread_create(&threads[i], NULL, sum_array, (void*)&thread_items[i]) != 0){
            fprintf(stderr, "Error creating thread %d\n", i);
            return 1;
        }
    }
    for(int i =0; i < MAX_THREADS; i++){
        pthread_join(threads[i], NULL);
        printf("Thread %d: Sum = %lld\n", thread_items[i].thread_id, thread_items[i].sum);
    }
    end = clock();
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", cpu_time_used);


    return 0;
}