#include<unistd.h>

#include<stdio.h>

void main()
{
    pid_t child, grandchild1, grandchild2;
 
    printf("Parent process N1 and pid %d\n", getpid());

    child = fork();
    if(child == 0)
    {
        // child
        printf("Child process N2 and pid is %d\n", getpid());

        grandchild1 = fork();
        if (grandchild1 == 0)
        {
            // grandchild1
            printf("Grandchild1 N3 and pid is %d parent pid %d\n", getpid(),getppid());
            
        }
       else if (grandchild1 > 0)
        {
           
            grandchild2 = fork();
            if (grandchild2 == 0)
            {
                // grandchild2
                printf("Grandchild2 N4 and pid is %d parent pid %d \n", getpid() , getppid());
               
            }
          
           }
    }
    
}
