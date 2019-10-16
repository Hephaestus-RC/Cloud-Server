#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{		
	pid_t id = fork();	
	pid_t ret,ret2;	
	if(id < 0)
	{			
		perror("fork failed!\n");			
		exit(0);
	}
	else if(id == 0)
	{
		sleep(1000);
		exit(10);
	}
	else
	{
		//bit opertion
		int st;
		ret = wait(&st);
		printf("bit operation # \n");
		if(ret > 0 && (st & 0x7F) == 0)  
			printf("child exit code : %d \n",(st>>8)&0xFF);	
		else if(ret > 0)  
			printf("signal code : %d \n ",st & 0x7F);
		
		//macro operation
		printf("\nmacro operation # \n");
		if(ret > 0 && WIFEXITED(st))	
			printf("child exit code : %d \n",WEXITSTATUS(st));
		else if(ret > 0)
			printf("signal code : %d \n ",st&0x7F);
	}
		return 0;
}		
