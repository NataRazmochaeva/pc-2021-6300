#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int wait(int *stat_loc);

int main(void) {
    pid_t pid, pid1, pid2, pid3;

    printf("Parent start\n");
    printf(" Parent PID :: %i\n",getpid());
    printf(" Parent parent PID :: %i\n",getppid());

    pid = fork();

    if ( pid < 0 ) {
        return 1;
    }
    else if ( pid == 0 ) {
        // in п1
        printf("\tп1 start\n");
        printf("\t п1 PID :: %i\n",getpid());
        printf("\t п1 parent PID :: %i\n",getppid());
        pid1 = fork();
        
        if ( pid1 < 0 ) {
            return 1;
        }
        else if ( pid1 == 0 ) {
            // in п2
            printf("\t\tп2 start\n");
            printf("\t\t п2 PID :: %i\n",getpid());
            printf("\t\t п2 parent PID :: %i\n",getppid());
            pid2 = fork();
            pid3 = fork();

            if ( pid2 < 0 ) {
                return 1;
            }
            else if ( pid2 == 0 ) {
                // in п3
                printf("\t\t\tп3 start\n");
                printf("\t\t\t п3 PID :: %i\n",getpid());
                printf("\t\t\t п3 parent PID :: %i\n",getppid());
                return 0;
            }
            
            if ( pid3 < 0 ) {
                    return 1;
            }
            else if ( pid3 == 0 ) {
                // in п4
                printf("\t\tп4 start\n");
                printf("\t\t п4 PID :: %i\n",getpid());
                printf("\t\t п4 parent PID :: %i\n",getppid());
                return 0;
            }
        }
        }
}
