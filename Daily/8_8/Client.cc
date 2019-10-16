#include<iostream>
#include<unistd.h>
#include<string>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
using namespace std;

#define PATH "."
#define PROJ_ID 0x6660

int main()
{
	key_t key = ftok(PATH,PROJ_ID);
	if(key < 0)
	{
		cerr<<"ftok error!"<<endl;
		exit(1);
	}
	int shmid = shmget(key,4096,IPC_CREAT|0644);
	if(shmid < 0)
	{
		cerr<<"shmget error!"<<endl;
		exit(2);
	}
	char* msm = (char*)shmat(shmid,nullptr,0);
	//string msm = (char*)shmat(shmid,nullptr,0);
	cout<<"msm : "<<&msm<<endl;
	int i = 0;
	while(i<=26)
	{
		cout<<"client push :"<<msm<<endl;
		
		//msm.push_back('A'+i);
		
		msm[i] = 'A'+i;
		i++;
		msm[i] = 0;
		sleep(1);
	}
	//shmdt(msm.c_str());
	shmdt(msm);
	sleep(2);
	return 0;

}
