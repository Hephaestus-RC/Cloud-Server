#include<iostream>
#include<string>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<assert.h>
using namespace std;

#define NUM 32
#define SIZE 256

void CommandParse(char* cmd,char** args)
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
	i = 0;
	while(args[i])
	{
		cout<<args[i]<<endl;
		i++;
	}
	//for(int j = 0;j<strlen(cmd);++j)
	//{
	//	args[i++] = cmd;
	//	
	//	while(cmd[j]!=' ')
	//		++j;
	//	cmd[j] = '\0';
	//}
}
void ExecCommand(char** args)
{
	assert(args);
	string cmd = args[0];
	if(cmd == "cd")
	{
		chdir(args[1]);
		return ;
	}

	pid_t id = fork();
	if(id == 0)
	{
		execvp(args[0],args);
		exit(13);
	}
	else
	{
		int st = 0;
		waitpid(id,&st,0);
		
	}
}
int main()
{
	const string tip = "[rc@XXXX minishell]# ";
	char* args[NUM] = {NULL};
	while(1)
	{
		char cmd[SIZE];
		cout<<tip;
		fgets(cmd,sizeof(cmd)-1,stdin);
		cmd[strlen(cmd)-1] = 0;
		CommandParse(cmd,args);
		ExecCommand(args);
		//memset(cmd,0,sizeof(cmd));	
	}
	return 0;
}
