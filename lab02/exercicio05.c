#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>

#define n 15

int number_of_threads = n;
int fib[n];

void *calcular_fibonacci(void *tid) {
    size_t i = (size_t) tid;

    if (i == 0) {
        fib[0] = 1;
    } else if (i == 1) {
        fib[1] = 1;
    } else {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    pthread_exit(NULL);
}

void *mostrar_valor(void *tid) {
    printf("%d ", fib[(size_t) tid]);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[number_of_threads];

    // Criando threads para calcular a sequência de fibonacci
    for (int i = 0; i < number_of_threads; i++) {
        int status = pthread_create(&threads[i], NULL, calcular_fibonacci, (void *)(size_t) i);

        if (status != 0) {
            printf("Erro na criação da thread %d. Código de erro %d.", i, status);
            return 1;
        }

        pthread_join(threads[i], NULL);
    }

    // Criando threads para mostrar os elementos da sequência de fibonacci
    // que foram criados anteriormente
    for (int i = 0; i < number_of_threads; i++) {
        int status = pthread_create(&threads[i], NULL, mostrar_valor, (void *)(size_t) i);

        if (status != 0) {
            printf("Erro na criação da thread %d. Código de erro %d.", i, status);
            return 1;
        }

        pthread_join(threads[i], NULL);
    }

    printf("\n");

    return 0;
}