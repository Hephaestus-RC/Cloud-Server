#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE 256

void AnalysisCmd(char* cmd,char** args)
{
    if(cmd == NULL || args == NULL)
		return ;
	int i = 0;
	args[i++] = strtok(cmd," ");
	while(1)
	{
	    args[i++] = strtok(NULL," ");
		if(args[i] == NULL)
				break;
		i++;
	}
	//`Replace(args);
}
void Replace(char** args)
{
    pid_t id = fork();
	if(id == 0)
	{
		execvp(args[0],args);
		exit(1);
	}
	else
	{
		waitpid(id,NULL,0);
	}
}

int main()
{
    const char* msg= "[rc@host 7252]# ";
	char* args[] = {NULL};
	
	while(1)
	{
		printf("[rc@host 7252]# ");
		char cmd[MAX_SIZE];
		scanf("%s",cmd);
		fflush(stdin);
		//analysis cmd
		AnalysisCmd(cmd,args);
		//function replace
		Replace(args);
	}
	return 0;
}
