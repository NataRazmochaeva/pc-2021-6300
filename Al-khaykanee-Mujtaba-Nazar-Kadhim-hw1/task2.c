#include<unistd.h>

#include<stdio.h>

void main()
{
    pid_t parent , child1 , child2, grandchild;
 
    printf("Parent process N1 and pid %d\n", getpid());

  child1 = fork();
        if (child1 == 0)
        {
            // child1
            printf("child1 N2 and pid is %d  parent pid is %d\n", getpid(),getppid());
            
        }
       else if (child1 > 0)
        {
           
            child2 = fork();
            if (child2 == 0)
            {
                // child2
                printf("child2 N3 and pid is %d and parent pid is %d\n", getpid(),getppid());
               
        
            grandchild = fork();
            if (grandchild == 0)
            {
                printf("N3 parent of N4 and pid is  %d\n",getppid());
                //grandchild
                printf("Grandchild N4 and child of N3 and pid is %d\n", getpid());
            }
            }
           }
    }
    
    

       
