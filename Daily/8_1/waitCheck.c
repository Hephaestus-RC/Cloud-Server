#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/wait.h>

void handler(int signo)
{
	pid_t id = 0;
	while((id = waitpid(-1,NULL,WNOHANG))>0)
	{
		printf("wait child success : %d\n",id);
	}
	printf("child quir...\n");
}

int main()
{
	signal(SIGCHLD,handler);
	pid_t id;
	if((id = fork()) == 0)
	{
		printf("child id :%d\n",getpid());
		sleep(2);
		exit(0);
	}
	while(1)
	{
		printf("father proc is doing something\n");
		sleep(1);
	}
	return 0;

}
