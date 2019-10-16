#include<iostream>
#include<string>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
using namespace std;

#define PATH "."
#define PROJ_ID 0x6660

int main()
{
	key_t key = ftok(PATH,PROJ_ID);
	if(key<0)
	{
		cerr<<"ftok error"<<endl;
		exit(1);
	}
	int shmid = shmget(key,4096,IPC_CREAT|IPC_EXCL|0644);
	if(shmid < 0)
	{
		cerr<<"shmget error!"<<endl;
		exit(1);
	}
	//string msm=(char*)shmat(shmid,nullptr,0);
	char* msm = (char*)shmat(shmid,nullptr,0);
	cout<<"msm : "<<&msm<<endl;
	int i = -1;
	while(i++<=25)
	{
		cout<<"Server :"<<msm<<endl;
		sleep(1);
	}
	shmdt(msm);
	//shmdt(msm.c_str());
	sleep(2);
	shmctl(shmid,IPC_RMID,nullptr);
	return 0;
}
