#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    printf("Sou o processo %d e estou executando o meu próprio programa.\n", getpid());
    sleep(30);

    return 0;
}