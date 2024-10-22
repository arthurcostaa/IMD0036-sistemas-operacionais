/*
Realizando a comunicação de processos utilizando uma área de memória
comportilhada. Nesse exemplo foi criado apenas um processo, a área de
memória, foi feito o anexo dessa área de memória ao processo, a adição
de uma mensagem na região de memória e também a desanexação e remoção
do segmento de memória utilizando
*/

#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>

int main() {
    // Identificador do segmento de memória compartilhada
    int segment_id;
    // Ponteiro do segmento de memória compartilhada
    char* shared_memory;
    // Tamanho em bytes do segmento de memória compartilhada
    const int segment_size = 4096;

    // Aloca um segmento de memória compartilhada
    segment_id = shmget(IPC_PRIVATE, segment_size, S_IRUSR | S_IWUSR);

    // Anexa o segmento de memória compartilhada
    shared_memory = (char *) shmat(segment_id, NULL, 0);
    printf("Segmento de memória %d anexado no endereço %p\n", segment_id, shared_memory);

    // Grava uma mensagem no segmento de memória compartilhada
    sprintf(shared_memory, "Hello, World!");

    // Exibe a string a partir da memória compartilhada
    printf("*%s*\n", shared_memory);

    // Desanexa o segmento de memória compartilhada
    if (shmdt(shared_memory) == -1) {
        fprintf(stderr, "Não é possível desanexar\n");
    }

    // Remove o segmento de memória compartilhada
    shmctl(segment_id, IPC_RMID, NULL);

    return 0;
}