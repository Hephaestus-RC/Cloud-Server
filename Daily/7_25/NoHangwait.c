#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>

int main()
{
   pid_t id = fork();
   if(id < 0)
   {
		perror("fork failed\n");
   }
   else if(id == 0)
   {
		printf("child sleep...\n");
		sleep(3);
		exit(257);
   }
   else
   {
		int st;
		pid_t ret = waitpid(id,&st,WNOHANG);
		if(ret == id &&((st&0X8F )==0))
		{
		    printf("wait success,child return code:%d\n",(st>>8)&0XFF);
		}
		else
		{
		    printf("wait failed,signed=\n",st&0X7F);
		}
		return 0;
   }
}
