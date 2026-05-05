#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>
#include<pthread.h>

#define MAX_EL 4
#define MAX_THREADS 4


long long int mat1[MAX_EL][MAX_EL];
long long int mat2[MAX_EL][MAX_EL];
long long int result[MAX_EL][MAX_EL];



typedef struct{
    int row_index;

}thread_item;

void assign_matrix(){
    for(int i = 0; i < MAX_EL; i++){
        for(int j = 0; j < MAX_EL; j++){
            mat1[i][j] = (long long int)pow(i, 2) + (long long int)pow(j, 2);
            mat2[i][j] = (long long int)pow(i, 3) + (long long int)pow(j, 3);
        }
    }
    return;
}

void* handle_row(void*arg){
    thread_item* item = (thread_item*) arg;
    int row_index = item -> row_index;
    for(int j = 0; j < MAX_EL; j++){
        result[row_index][j] = 0;
        for(int k = 0; k < MAX_EL; k++){
            result[row_index][j] += mat1[row_index][k] * mat2[k][j];
        }
    }
    return NULL;
}

int main(){

    assign_matrix();
    time_t start, end;
    double cpu_time_used;
    start = clock();

    pthread_t threads[MAX_THREADS];
    thread_item thread_items[MAX_THREADS];
    for(int i = 0; i < MAX_THREADS; i++){
        thread_items[i].row_index = i;
        if(pthread_create(&threads[i],NULL,handle_row, (void*)&thread_items[i]) != 0){
            fprintf(stderr, "Error creating thread %d\n", i);
            return 1;
        }
    }
    for(int i = 0; i < MAX_THREADS; i++){
        pthread_join(threads[i], NULL);
    }


    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", cpu_time_used);


    return 0;
}