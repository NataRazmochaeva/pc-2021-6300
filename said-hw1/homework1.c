// Task1 Linear structure of processes: P1 -> P2 -> P3 + P4

#include <stdio.h> 
#include <unistd.h>



int main() 
{ 
    pid_t pid, pid_3, pid_4;
    int status, status2, status3;
    printf(" Parent Parent  id: %d\n", getpid()); 

    pid = fork();
    wait(&status);

    if (pid == 0) {    
        printf("child1  id: %d\n", getpid()); 
        printf("  Parent child1 id: %d\n", getppid());

        pid_3 = fork();
	
	wait(&status2);
	

        if (pid_3 == 0){
            printf("child2 id: %d\n", getpid()); 
            printf("Parent chid2 id: %d\n", getppid()); 
	    return 0;
        }
	
	pid_4 = fork();
	wait(&status3);

	if (pid_4 == 0){
	    printf("child3 id: %d\n", getpid());
	    printf("Parent child3 id: %d\n", getppid());
	}
    }

    exit(0);
} 
