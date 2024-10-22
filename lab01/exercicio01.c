#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    printf("Eu sou o processo %d\n", getpid());

    fork();
    fork();
    fork();
    fork();

    while (1) {
        pid_t pid = wait(NULL);

        if (pid == -1) {
            printf("Sou o processo %d, serei encerrado agora.\n", getpid());
            exit(0);
        } else {
            printf(
                "Sou o processo %d, meu filho %d terminou a sua execução.\n",
                getpid(),
                pid
            );
        }
    }

    return 0;
}