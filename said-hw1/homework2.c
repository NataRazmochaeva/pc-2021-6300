// Linear structure of processes: P1 -> P2 + P3 -> P4

#include <unistd.h>
#include <stdio.h>


int main() 
{ 
    pid_t pid, pid_3, pid_4;
    int status, status3, status4;
    printf("Parent Parent id: %d\n", getpid()); 

    pid = fork();
    wait(&status);

    if (pid == 0) {    
        printf("chil1 id: %d\n", getpid()); 
        printf("Parent child1 id: %d\n", getppid());

        pid_3 = fork();
	
	wait(&status3);
	

        if (pid_3 == 0){
            printf("chld2 id: %d\n", getpid()); 
            printf("Parent child2 id: %d\n", getppid()); 
	    
	    pid_4 = fork();
	    wait(&status4);

	    if (pid_4 == 0) {
		    printf("child3  id: %d\n", getpid());
		    printf("Parent child3 id: %d\n", getppid());
	    }
	}
    }

    exit(0);
} 
