#include<unistd.h>

#include<stdio.h>

void main()
{
    pid_t GrandDad , parent1 , parent2, child;
 
    printf("GrandDad first process and its pid is %d\n", getpid());
    printf("Parent process has id %d\n", getppid());

  parent1 = fork();
        if (parent1 == 0)
        {
            // parent1
            printf("parent1 second proces and its pid is %d\n", getpid());
            
        }
       else if (parent1 > 0)
        {
           
            parent2 = fork();
            if (parent2 == 0)
            {
                // parent2
                printf("parent2 third process and its pid is %d\n", getpid());
               
        
            child = fork();
            if (child == 0)
            {
                //child
                printf("Child of the third process and its pid is %d\n", getpid());
            }
            }
           }
    }
    
