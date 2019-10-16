#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>

#define PATH "."
#define PROJ_ID 0x6666

int main()
{
	key_t key = ftok(PATH,PROJ_ID);
	if(key<0)
	{
		perror("ftok error\n");
		exit(0);
	}
	int shmid = shmget(key,4096,IPC_CREAT|IPC_EXCL|0644);
	int i = 0;
	//shmctl(shmid,IPC_RMID,NULL);
	if(shmid < 0)
	{
		perror("shmget error\n");
		exit(1);
	}
	char* msm = shmat(shmid,NULL,0);
	while(i++<=26)
	{
		printf("server #%s\n",msm);
		sleep(1);
	}
	shmdt(msm);
	shmctl(shmid,IPC_RMID,NULL);
	return 0;
}
