#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        printf("Sou o processo %d e não consegui criar um novo processo.\n", getpid());
        return 1;
    } else if (pid == 0) {
        printf("Sou o processo filho e meu PID é %d.\n", getpid());
    } else {
        printf("Sou o processo pai do %d, meu PID é %d.\n", pid, getpid());
        wait(NULL);
    }

    return 0;
}