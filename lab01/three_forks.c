#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    fork();
    fork();
    fork();
    printf("Sou o processo %d.\n", getpid());

    return 0;
}