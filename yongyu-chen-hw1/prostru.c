// C Code for task1
#include <stdlib.h>
#include <stdio.h> 
#include <unistd.h>
#include <sys/types.h>

int wait(int *stat_loc);

int main() 
{ 
    pid_t pid, pid_3, pid_4;
    int status, status3, status4;
    printf("				n1 Process id: %d\n", getpid()); 

    pid = fork();
    wait(&status);

    if (pid == 0) {    
        printf("				n2 Process id: %d\n", getpid()); 
        printf("				Parent id: %d\n", getppid());

        pid_3 = fork();
	
	wait(&status3);
	

        if (pid_3 == 0){
            printf("n3 Process id: %d\n", getpid()); 
            printf("Parent id: %d\n", getppid()); 
	    return 0;
        }
	
	pid_4 = fork();
	wait(&status4);

	if (pid_4 == 0){
	    printf("						n4 Process id: %d\n", getpid());
	    printf("						Parent id: %d\n", getppid());
	}
    }

    exit(0);
} 
