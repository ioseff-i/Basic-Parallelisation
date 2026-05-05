#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <pthread.h>

#define MAX_EL 1000
#define MAX_THREADS 8 // Locked to 4 CPU cores

// Global Matrices
long long int mat1[MAX_EL][MAX_EL];
long long int mat2[MAX_EL][MAX_EL];
long long int result[MAX_EL][MAX_EL];

// The Struct: A thread only needs its ID and the total number of workers
typedef struct {
    int thread_id;
    int num_threads;
} thread_item;

void assign_matrix() {
    for(int i = 0; i < MAX_EL; i++) {
        for(int j = 0; j < MAX_EL; j++) {
            mat1[i][j] = (long long int)pow(i, 2) + (long long int)pow(j, 2);
            mat2[i][j] = (long long int)pow(i, 3) + (long long int)pow(j, 3);
        }
    }
}

// The Thread Worker Function
void* handle_row(void* arg) {
    thread_item* item = (thread_item*) arg;
    int t_id = item->thread_id;
    int stride = item->num_threads;

    // THE STRIDE LOOP
    // Start at this thread's ID, and jump forward by 4 each time.
    for(int row_index = t_id; row_index < MAX_EL; row_index += stride) {
        
        // Standard Matrix Math for the specific row
        for(int j = 0; j < MAX_EL; j++) {
            result[row_index][j] = 0;
            for(int k = 0; k < MAX_EL; k++) {
                result[row_index][j] += mat1[row_index][k] * mat2[k][j];
            }
        }
    }
    return NULL;
}

int main() {
    assign_matrix();
    
    // Set up the Real-World Wall Clock Timer
    struct timespec start, end;
    double time_used;
    clock_gettime(CLOCK_MONOTONIC, &start);

    pthread_t threads[MAX_THREADS];
    thread_item thread_items[MAX_THREADS];
    
    // 1. Launch the 4 threads
    for(int i = 0; i < MAX_THREADS; i++) {
        thread_items[i].thread_id = i;
        thread_items[i].num_threads = MAX_THREADS;
        
        if(pthread_create(&threads[i], NULL, handle_row, (void*)&thread_items[i]) != 0) {
            fprintf(stderr, "Error creating thread %d\n", i);
            return 1;
        }
    }
    
    // 2. Wait for the 4 threads to finish all 100 rows
    for(int i = 0; i < MAX_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    // Stop the Timer
    clock_gettime(CLOCK_MONOTONIC, &end);
    time_used = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
    
    printf("Real time taken: %f seconds\n", time_used);

    return 0;
}