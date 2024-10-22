#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>

int number_of_threads = 5;

// Função usada pelas threads para dizer 'Olá!'
void *print_hello(void *tid) {
    printf("Olá, eu sou a thread %d\n", (int)(size_t) tid);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[number_of_threads];

    for (int i = 0; i < number_of_threads; i++) {
        // Criando uma thread e passando para ela a funcao printHello
        int status = pthread_create(&threads[i], NULL, print_hello, (void *)(size_t) i);

        if (status != 0) {
            printf("Erro na criação da thread %d. Código de erro: %d\n", i, status);
            return 1;
        }

        // Faz a thread principal esperar pela thread filha. Similar a funcao wait.
        pthread_join(threads[i], NULL);
    }

    return 0;
}