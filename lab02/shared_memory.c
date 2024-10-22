#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>

int main() {
    // Criando o segmento de memoria compartilhada com o tamanho de 10 chars
    int segment_id = shmget(IPC_PRIVATE, 10 * sizeof(char), S_IRUSR | S_IWUSR);

    // Criando o ponteiro que vai apontar para o endereço de memória compartilhada
    char *shared_memory;

    pid_t pid = fork();

    if (pid < 0) {
        printf(
            "Sou o processo %d e não consegui criar um novo processo.\n",
            getpid()
        );
        return 1;
    } else if (pid == 0) {
        // Anexando o segmento de memoria compartilhada
        shared_memory = (char *) shmat(segment_id, NULL, 0);

        // Escrevendo na memória compartilhada
        sprintf(
            shared_memory,
            "Olá, processo pai, sou o seu filho e o meu ID é %d.",
            getpid()
        );

        // Desanexando a memória compartilhada
        shmdt(shared_memory);

        // Encerrando o processo filho
        exit(0);
    } else {
        // Fazendo o pai esperar que o filho termine de escrever
        wait(NULL);

        // Salvando o ponteiro que aponta para a memória compartilhada
        shared_memory = (char *) shmat(segment_id, NULL, 0);

        // Imprimindo mensagem deixada pelo processo filho
        printf("%s\n", shared_memory);

        // Removendo o segmento de memória compartilhada
        shmctl(segment_id, IPC_RMID, NULL);
    }

    return 0;
}