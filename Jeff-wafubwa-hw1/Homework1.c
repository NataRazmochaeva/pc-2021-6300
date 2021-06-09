#include<stdio.h>
#include<unistd.h>

int main () {
  
int  i ; 
pid_t p,q; 

ppid = getppid();
 printf("P1%d\n", ppid);

p=fork();
  if(p==0) {
   for (i=1 ; i<=2; i++){
      q=fork();
     pid=getpid();

    if (p==0){ 

        printf("P%d %d%d\n",i++, pid);

        break;
    }
        } while (wait(0)>0){

        } 
        {
          return 0;
        }
}  
}
