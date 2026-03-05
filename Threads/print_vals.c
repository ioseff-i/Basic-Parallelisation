#include<stdio.h>
#include<pthread.h>

void* job1(void* arg){
    printf("This is a printer of job1!\n");
    return NULL;
}
void* job2(void* arg){
    printf("This is a printer of job2!\n");
    return NULL;
}
void* job3(void* arg){
    printf("This is a printer of job3!\n");
    return NULL;
}
int main(){
    pthread_t t1,t2,t3,t4,t5,t6;

    pthread_create(&t1,NULL,job1,NULL);
    pthread_create(&t2,NULL,job2,NULL);
    pthread_create(&t3,NULL,job3 ,NULL);
    pthread_create(&t4,NULL,job1,NULL);
    pthread_create(&t5,NULL,job2,NULL);
    pthread_create(&t6,NULL,job3 ,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    pthread_join(t4,NULL);
    pthread_join(t5,NULL);
    pthread_join(t6,NULL);

    printf("All threads have finished their job!\n");


    return 0;
}