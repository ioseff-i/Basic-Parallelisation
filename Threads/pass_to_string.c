#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* job(void* arg) {
    char* str = (char*)arg;
    printf("The string passed to the thread is: %s\n", str);
    return NULL;
}

int main() {
    int num_threads, num_strings;

    printf("Enter the number of threads: ");
    scanf("%d", &num_threads);

    printf("Enter the number of strings: ");
    scanf("%d", &num_strings);

    pthread_t* threads = malloc(num_threads * sizeof(pthread_t));
    char** strings = malloc(num_strings * sizeof(char*));

    for (int i = 0; i < num_strings; i++) {
        strings[i] = malloc(100 * sizeof(char));
        printf("Enter string %d: ", i + 1);
        scanf("%s", strings[i]);
    }

    for (int i = 0; i < num_threads; i++) {
        int index = i % num_strings;       // ← no malloc needed
        pthread_create(&threads[i], NULL, job, strings[index]);
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    for (int i = 0; i < num_strings; i++) {
        free(strings[i]);
    }
    free(strings);
    free(threads);

    return 0;
}