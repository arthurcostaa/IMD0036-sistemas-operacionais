#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>

int n = 20;

int main() {
    // Criando o segmento de memoria compartilhada com o tamanho de n ints
    // para armazenar a sequencia de Fibonacci
    int segment_id = shmget(IPC_PRIVATE, n * sizeof(int), S_IRUSR | S_IWUSR);

    // Criando o ponteiro que vai apontar para o endereço de memória compartilhada
    int *shared_memory;

    pid_t pid = fork();

    if (pid < 0) {
        printf("Sou o processo %d e não consegui criar um novo processo.\n", getpid());
        return 1;
    } else if (pid == 0) {
        // Anexando o segmento de memoria compartilhada
        shared_memory = (int *) shmat(segment_id, NULL, 0);

        if (n == 1) {
            shared_memory[0] = 1;
        } else if (n == 2) {
            shared_memory[0] = 1;
            shared_memory[1] = 1;
        } else {
            shared_memory[0] = 1;
            shared_memory[1] = 1;
            for (int i = 2; i < n; i++) {
                shared_memory[i] = shared_memory[i - 1] + shared_memory[i - 2];
            }
        }

        // Desanexando a memória compartilhada
        shmdt(shared_memory);

        // Encerrando o processo filho
        exit(0);
    } else {
        // Fazendo o pai esperar que o filho termine de escrever os valores
        // na área de memória compartilhada
        wait(NULL);

        // Salvando o ponteiro que aponta para a memória compartilhada
        shared_memory = (int *) shmat(segment_id, NULL, 0);

        // Imprimindo conteúdo deixado pelo processo filho
        // na área de memória compartilhada
        for (int i = 0; i < n; i++) {
            printf("%d ", shared_memory[i]);
        }
        printf("\n");

        // Removendo o segmento de memória compartilhada
        shmctl(segment_id, IPC_RMID, NULL);
    }

    return 0;
}