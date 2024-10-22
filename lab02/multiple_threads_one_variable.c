#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>

// Variavel global que define o numero de threads
int number_of_threads = 5;
// Variável global que define valor
int valor = 0;

// Funcao que as threads vao usar para alterar valor
void *altera_valor(void *tid) {
    valor += 5;
    printf("Olá, eu sou a thread %d. Eu alterei valor para %d\n", (int)(size_t) tid, valor);
    pthread_exit(NULL);
}

int main(int argc, char **argv) {
    pthread_t threads[number_of_threads];

    for (int i = 0; i < number_of_threads; i++) {
        // Criando uma thread e passando para ela a função altera_valor
        int status = pthread_create(&threads[i], NULL, altera_valor, (void *)(size_t) i);

        // Se o status nao for 0, houve um erro na criacao da thread
        if (status != 0) {
            printf("Erro na criação da thread %d. Código de erro %d.", i, status);
            return 1;
        }

        // Faz a thread principal esperar pela thread filha. Similar a funcao wait.
        pthread_join(threads[i], NULL);
    }

    printf("Olá, eu sou a thread original. Valor é igual a %d\n", valor);
    return 0;
}