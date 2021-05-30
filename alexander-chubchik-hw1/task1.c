#include<unistd.h>

#include<stdio.h>

void main()
{
    pid_t Parent, child1, child2;
 
    printf("This is first process and its pid is %d\n", getpid());
    printf("Parent process has id %d\n", getppid());

    Parent = fork();
    if(Parent == 0)
    {
        //this is the child
        printf("This is second process and its pid is %d\n", getpid());

        child1 = fork();
        if (child1 == 0)
        {
            // child1
            printf("This is third process and its pid is %d\n", getpid());
            
        }
       else if (child1 > 0)
        {
           
            child2 = fork();
            if (child2 == 0)
            {
                // child2
                printf("This is fourth process and its pid is %d\n", getpid());
               
            }
          
           }
    }
    
}
       
    
 



