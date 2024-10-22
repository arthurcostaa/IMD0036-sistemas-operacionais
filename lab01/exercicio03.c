#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int x = 100;

void increment(int* value) {
    *value += 100;
}

int main() {
    pid_t pid1 = fork();

    if (pid1 == 0) {
        increment(&x);

        pid_t pid2 = fork();
        if (pid2 == 0) {
            increment(&x);
            printf("processo neto: x = %d\n", x);
            exit(0);
        } else {
            wait(NULL);
            printf("processo filho: x = %d\n", x);
        }

        exit(0);
    } else {
        wait(NULL);
    }

    printf("processo pai: x = %d\n", x);

    return 0;
}