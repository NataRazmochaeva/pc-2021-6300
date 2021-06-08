#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
int main()
{
   int i;
   pid_t p,q;
	printf("P1\n");
	for(i=0;i<2;i++)
	{
	p=fork();
    pid=getpid();

	if(p==0)
		{
		printf("P%d%d\n",i+1, pid);
        
      if(i==1){
          q=fork();

          pid=getpid();
          printf("P4%d\n", pid)
      }

		break;

		}
	}while(wait(0)>0);
return 0;
}