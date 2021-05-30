#include<unistd.h>
#include<stdio.h>
void main()
{

    pid_t n2,n3,n4;
 
    printf("I'm n1 and my pid is  %d\n", getpid());
    

  n2= fork();
        if (n2 == 0)
        {
            printf("I'm n2 and my pid is %d \n", getpid()); 
   printf("and my father is n1 and his pid  %d \n", getppid());
         
        }
        else if (n2>0)
        {
        n3=fork();
         if (n3 == 0)
         {
        printf("I'm n3 and my pid is %d \n", getpid()); 
   printf("and my father is n1 and his pid  %d \n", getppid());  
         
  
      n4= fork();
        if (n4 == 0)
         {
        printf("I'm n4 and my pid is %d \n", getpid()); 
   printf("and my father is n4 and his pid  %d \n", getppid());  
         }
      
    }
        }
}
