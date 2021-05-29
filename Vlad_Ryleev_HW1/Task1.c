#include<unistd.h>
#include<stdio.h>

void main()
{
    pid_t Father, child1, child2;
 
    printf("Pid of the first process %d\n", getpid());

    Father = fork();
    if(Father == 0)
    {
       printf("Pid of the second process %d\n", getpid());

        child1 = fork();
        if (child1 == 0)
        {
            // child1
            printf("Pid of the third process %d\n", getpid());
            
        }
       else if (child1 > 0)
        {
           
            child2 = fork();
            if (child2 == 0)
            {
                // child2
                printf("Pid of the fourth process %d\n", getpid());
               
            }
          
           }
    }
    
}
       
    
 



