#include<stdio.h>
#include<unistd.h>

int main()
{

	pid_t id = fork();
	if(id < 0)
		perror("fork failed\n");
	else if(id == 0)
	{
		printf("子进程\n");
		return 0;
	}
		
	else
	{
		printf("父进程\n");
		return 0;	
	}
}
