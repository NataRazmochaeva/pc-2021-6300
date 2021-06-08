#include<stdio.h>
#include<unistd.h>

int main () {
  
int  i ; 
pid_t p,q,d,c; 

ppid=getppid();
printf("P1%d\n", ppid);

   p=fork();
   if(p==0){
       pid=getpid();
     printf("P2%d\n", pid)

     q=fork();
     if(q==0){

         pid=getpid();
         printf("P3%d\n",pid);
         
         d=fork();
         
         if (d==0){
             pid=getpid();
             printf("P4%d\n", pid); 

         }
              }

   } break; 

   
        } 
        
          
        

