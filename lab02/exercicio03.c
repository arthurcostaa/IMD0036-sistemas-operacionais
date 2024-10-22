#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/stat.h>

const int n = 15;

int main() {
    int segment_id = shmget(IPC_PRIVATE, n * sizeof(int), S_IRUSR | S_IWUSR);
    int* shared_memory;

    shared_memory = (int *) shmat(segment_id, NULL, 0);

    // Definindo o valor inicial da área de memória para 0 usando o processo pai
    *shared_memory = 0;

    shmdt(shared_memory);

    printf("0 ");

    fflush(stdout);

    for (int i = 1; i <= n; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            printf("Erro ao criar um novo processo.\n");
            return 1;
        } else if (pid == 0) {
            shared_memory = (int *) shmat(segment_id, NULL, 0);
            *shared_memory += i;
            shmdt(shared_memory);
            printf("+ %d ", i);
            exit(0);
        } else {
            wait(NULL);
        }
    }
    printf("= ");

    shared_memory = (int *) shmat(segment_id, NULL, 0);
    printf("%d\n", *shared_memory);
    shmdt(shared_memory);

    shmctl(segment_id, IPC_RMID, NULL);

    return 0;
}