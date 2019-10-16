#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

#define MAXSIZE 1024
int main()
{
	char buf[MAXSIZE];
	pid_t pid;
	int status;



	printf("[xx@XXX hostlocal]@");
	while(fgets(buf,sizeof(buf),stdin) )
	{
		if(buf[strlen(buf)-1] == '\n')
			buf[strlen(buf)-1] = 0;
	
		if(pid = fork() < 0)
			perror("fork error!");
		else if(pid == 0)
		{
			execlp(buf,buf,(char*)0);
			printf("Couldn't execute : %s\n",buf);
			exit(127);
		}
		if(pid = waitpid(pid,&status,0) < 0)
			perror("waitpid error!");
		//printf("%%");

	}
	exit(0);
}
