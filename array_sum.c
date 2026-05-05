#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
#include<math.h>



#define MAX_EL 10000000


long long int array1[MAX_EL];
long long int array2[MAX_EL];
long long int array3[MAX_EL];
long long int array4[MAX_EL];


void assign_array(){
    for(int i = 0; i < MAX_EL; i++){
        array1[i] = pow(i, 2);
        array2[i] = pow(i, 3);
        array3[i] = pow(i, 4);
        array4[i] = pow(i, 5);
    }
    return;
}
long long int sum_array(long long int *array){
    long long int sum = 0;
    for(int i = 0; i < MAX_EL; i++){
        sum += array[i];
    }
    return sum;
}

int main(){
    assign_array();
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    long long int sum1 = sum_array(array1);
    long long int sum2 = sum_array(array2);
    long long int sum3 = sum_array(array3);
    long long int sum4 = sum_array(array4);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Sum of array 1: %lld\n", sum1);
    printf("Sum of array 2: %lld\n", sum2);
    printf("Sum of array 3: %lld\n", sum3);
    printf("Sum of array 4: %lld\n", sum4);
    printf("Time taken: %f seconds\n", cpu_time_used);
    
    return 0;
}