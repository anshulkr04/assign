#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
    pid_t pid1, pid2;
    int status;

    // Print parent process information
    printf("Process PID: %d, Role: Parent\n", getpid());

    // Create first child
    pid1 = fork();

    if (pid1 < 0) {
        // Fork failed
        fprintf(stderr, "Fork Failed\n");
        return 1;
    }
    else if (pid1 == 0) {
        // First child process
        printf("Process PID: %d, Role: Child 1\n", getpid());
        exit(0);
    }
    else {
        // Parent process creates second child
        pid2 = fork();

        if (pid2 < 0) {
            // Fork failed
            fprintf(stderr, "Fork Failed\n");
            return 1;
        }
        else if (pid2 == 0) {
            // Second child process
            printf("Process PID: %d, Role: Child 2\n", getpid());
            exit(0);
        }
        else {
            // Parent process waits for both children
            waitpid(pid1, &status, 0);
            printf("Child with PID: %d, Role: Child 1 has exited\n", pid1);
            
            waitpid(pid2, &status, 0);
            printf("Child with PID: %d, Role: Child 2 has exited\n", pid2);

            // Parent's final message before exit
            printf("Process PID: %d, Role: Parent - Exiting\n", getpid());
            exit(0);
        }
    }
    return 0;
}