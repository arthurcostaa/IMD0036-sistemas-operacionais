#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int x = 100;

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        printf("Erro ao criar um novo processo.\n");
        return 1;
    } else if (pid == 0) {
        x += 100;
        printf("%d\n", x);
        exit(0);
    } else {
        wait(NULL);
    }

    printf("Valor da variável x = %d\n", x);

    return 0;
}