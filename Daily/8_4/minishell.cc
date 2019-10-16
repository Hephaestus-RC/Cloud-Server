#include<iostream>
#include<string>
#include<cstring>
#include<vector>
#include<assert.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
using namespace std;

void ParseCommend(string& cmd,char** args)
{
	//assert(cmd!=NULL);
	//assert(args!=NULL);
	int j = 0;
	args[j++]=&cmd[0];
	for(int i = 1;i<cmd.size();++i)
	{
		if(cmd[i]==' ')
		{
			cmd[i]='\n';
			args[j++]=&cmd[i+1];
		}
	}
	j = 0;
	while(args[j]!=NULL)
	{
		cout<<args[j++]<<endl;
	}
}
void Exec(char** args)
{
	//assert(args!=NULL);
	execvp(args[0],args);
	//return 1;
}
int main()
{
	string cmd;
	//vector<string> args;
	char* args[]={NULL};
	while(getline(cin,cmd))
	{
		pid_t id = fork();
		if(id < 0)
		{
			cerr<<("fork error!\n");
			return 0;
		}
		else if(id == 0)
		{
			ParseCommend(cmd,args);
			//Exec(args);
		}
		else
		{
			int st = 0;
			waitpid(id,&st,WNOHANG);
			cout<<"code : "<<(int)((st>>8)&0xFF)<<"sig : "<<(int)(st&0x7F)<<endl;
			return 0;
		}
	}
}
