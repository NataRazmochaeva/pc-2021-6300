#include<unistd.h>
#include<stdio.h>

void main()
{
    pid_t GrandFather , Father , Father2, child;
 
    printf("GrandFather's pid %d\n", getpid());
	printf("Parent process id %d\n", getppid());
	
  Father = fork();
        if (Father == 0)
        {
            // Father
            printf("Pid of the second process, father %d\n", getpid());
            
        }
       else if (Father > 0)
        {
           
            Father2 = fork();
            if (Father2 == 0)
            {
                // Father2
                printf("Pid of the third process, father2 %d\n", getpid());
               
        
            child = fork();
            if (child == 0)
            {
                //child
                printf("Pid Child of the third process %d\n", getpid());
            }
            }
           }
    }
    

       
    
 




       
    
 



