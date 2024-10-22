#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>

#define NUMBER_OF_THREADS 10

void *print_hello_world(void *tid) {
    printf("Olá, mundo! Boas vindas da thread %d\n", tid);
    pthread_exit(tid);
}

int main() {
    pthread_t threads[NUMBER_OF_THREADS];

    for (int i = 0; i < NUMBER_OF_THREADS; i++) {
        printf("Método main. Criando thread %d\n", i);
        int status = pthread_create(
            &threads[i], NULL, print_hello_world, (void *)(intptr_t)i
        );

        if (status != 0) {
            printf("Oops. pthread_create retornou um código de erro %d\n", status);
            exit(-1);
        }
    }

    return 0;
}