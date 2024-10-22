#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>

int main() {
    // Criando o segmento de memoria compartilhada com o tamanho de 1 int
    int segment_id = shmget(IPC_PRIVATE, sizeof(int), S_IRUSR | S_IWUSR);

    // Criando o ponteiro que vai apontar para o endereço de memória compartilhada
    int *shared_memory;

    // Anexando o segmento de memoria compartilhada ao processo pai
    shared_memory = (int *) shmat(segment_id, NULL, 0);

    // Gravando valor na memória compartilhada via processo pai
    *shared_memory = 1;

    printf("Valor inicial: %d\n", *shared_memory);

    // Desanexando a memória compartilhada
    shmdt(shared_memory);

    // Processo filho
    pid_t pid_filho = fork();

    if (pid_filho < 0) {
        printf("Sou o processo %d e não consegui criar o processo filho. T_T\n", getpid());
        return 1;
    } else if (pid_filho == 0) {
        // Anexando o segmento de memoria compartilhada
        shared_memory = (int *) shmat(segment_id, NULL, 0);

        // Escrevendo na memória compartilhada via processo
        *shared_memory += 1;

        // Desanexando a memória compartilhada
        shmdt(shared_memory);

        // Processo neto
        pid_t pid_neto = fork();

        if (pid_neto < 0) {
            printf("Sou o processo %d e não consegui criar o processo neto. T_T\n", getpid());
            return 1;
        } else if (pid_neto == 0) {
            // Anexando o segmento de memoria compartilhada
            shared_memory = (int *) shmat(segment_id, NULL, 0);

            // Escrevendo na memória compartilhada
            *shared_memory += 1;

            // Desanexando a memória compartilhada
            shmdt(shared_memory);

            printf("Processo neto escreveu na memória compartilhada.\n");

            // Encerrando o processo neto
            exit(0);
        } else {
            printf("Processo filho escreveu na memória compartilhada.\n");

            // Fazendo o processo filho esperar que o processo neto termine de escrever
            wait(NULL);
        }

        // Encerrando o processo filho
        exit(0);
    } else {
        printf("Processo pai escreveu na memória compartilhada.\n");

        // Fazendo o processo pai esperar que o processo filho termine de escrever
        wait(NULL);

        // Salvando o ponteiro que aponta para a memória compartilhada
        shared_memory = (int *) shmat(segment_id, NULL, 0);

        // Imprimindo o valor da área de memória compartilhada após
        // escritas feitas pelo processo filho e neto
        printf("Valor final: %d\n", *shared_memory);

        // Removendo o segmento de memória compartilhada
        shmctl(segment_id, IPC_RMID, NULL);
    }

    return 0;
}