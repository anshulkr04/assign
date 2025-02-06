#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main() {
    pid_t pid1, pid2;
    int status;
    int children = 2;

    pid1 = fork();
    
    switch(pid1) {
        case -1:
            perror("fork");
            exit(1);
        case 0:
            usleep(1000); 
            printf("ProcessID: %d, Role-Child 1 \n", getpid());
            exit(0);
        default:
            pid2 = fork();
            
            switch(pid2) {
                case -1:
                    perror("second fork");
                    exit(1);
                case 0: 
                    usleep(3000);
                    printf("ProcessID: %d, Role-Child 2\n", getpid());
                    exit(0);
            }
    }

    if (pid1 > 0 && pid2 > 0) {
        printf("ProcessID: %d, Role-Parent \n", getpid());

        while (children > 0) {
                        pid_t finished = wait(0);
                        printf("Child (ProcessID: %d) has exited\n", finished);
                        children--;
                    }
        
        printf("exiting ProcessID: %d, Role-Parent\n", getpid());
    }

    return 0;
}