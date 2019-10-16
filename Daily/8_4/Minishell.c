#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>

#define SIZE 1024

void ParseCommend(char* cmd,char** args)
{
	assert(cmd);
	assert(args);
	int i = 0;
	args[i++] = strtok(cmd," ");
	while(1)
	{
		args[i] = strtok(NULL," ");
		if(args[i] == NULL)
			break;
		i++;
	}
}

void ExecCommend(char** args)
{
	assert(args);
	//if(args == NULL)
	//	exit(1)
	//
	char* cmd = args[0];
	if(0==strcmp(cmd,"cd"))
	{
		chdir(args[1]);
		return;
	}
	pid_t id = fork();
	if(id < 0)
	{
		perror("fork failed!\n");
		exit(2);
	}
	else if(id == 0)
	{
		//child
		execvp(args[0],args);
		exit(3);
	}
	else
	{
		//father
		int st = 0;
		waitpid(id,&st,0);
		//printf("code : %d , sig : %d\n ",(st>>8)&0xFF,st&0x7F);
	}
}

int main()
{
	const char msg[] = "[rc@XXX hostlocal]# ";
	char* args[SIZE]={NULL};
	while(1)
	{
		char cmd[SIZE];
		printf("%s",msg);
		fgets(cmd,sizeof(cmd)-1,stdin);
		cmd[strlen(cmd)-1]=0;
		ParseCommend(cmd,args);
		ExecCommend(args);
	}
	return 0;
}
