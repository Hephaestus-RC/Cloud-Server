#include<iostream>
#include<cstring>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<assert.h>
using namespace std;

#define NUM 256
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
		if(args[i] ==  nullptr)
			break;
		i++;
	}
}

void ExecCommend(char** args)
{
	string cmd = args[0];
	if(cmd == "cd")
	{
		chdir(args[1]);
		return ;
	}
	//chongdingxiang --------- >>
	//
	//
	pid_t id = fork();
	if(id < 0)
	{
		cerr<<"fork failed\n";
		exit(0);
	}
	else if(id == 0)
	{
		execvp(args[0],args);
		exit(1);
	}
	else
	{
		int st;
		waitpid(id,&st,0);
		//cout<<"code : "<<(st>>8)&0XFF<<" sig : "<<st&0x7F<<endl;
	}
}
int main()
{
	const string tip = "[rc@XXX localhost ]* ";
	char* args[NUM];
	while(1)
	{
		char cmd[SIZE];
		cout<<tip;
		fgets(cmd,sizeof(cmd),stdin);
		//very important
		cmd[strlen(cmd)-1] = 0;
		ParseCommend(cmd,args);
		ExecCommend(args);
	}
	return 0;
}
