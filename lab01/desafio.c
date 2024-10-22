#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int n = 20;

int main() {
    printf("Processo pai (PID=%d)\n", getpid());
    fflush(stdout);

    pid_t pid = fork();

    if (pid == 0) {
        printf("Eu sou o processo filho (PID=%d)\n", getpid());
        if (n == 1) {
            printf("1");
        } else if (n == 2) {
            printf("1 2");
        } else {
            int nums[n];
            nums[0] = 1;
            nums[1] = 1;
            printf("1 2 ");
            for (int i = 2; i < n; i++) {
                nums[i] = nums[i - 1] + nums[i - 2];
                printf("%d ", nums[i]);
            }
            printf("\n");
        }
        exit(0);
    } else {
        wait(NULL);
    }

    return 0;
}