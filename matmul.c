#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

#define MAX_EL 1000
long long int mat1[MAX_EL][MAX_EL];
long long int mat2[MAX_EL][MAX_EL];
long long int result[MAX_EL][MAX_EL];

void assign_matrix(){
    for(int i = 0; i < MAX_EL; i++){
        for(int j = 0; j < MAX_EL; j++){
            mat1[i][j] = (long long int)pow(i, 2) + (long long int)pow(j, 2);
            mat2[i][j] = (long long int)pow(i, 3) + (long long int)pow(j, 3);
        }
    }
    return;
}

int main(){

    assign_matrix();
    time_t start, end;
    double cpu_time_used;
    start = clock();
    for(int i = 0; i < MAX_EL; i++){
        for(int j = 0; j < MAX_EL; j++){
            result[i][j] = 0;
            for(int k = 0; k < MAX_EL; k++){
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", cpu_time_used);


    return 0;
}