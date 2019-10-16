#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<stdlib.h>

#define PATH "."
#define PROJ_ID 0X6666 
int main()
{
	//get key 
	key_t key = ftok(PATH,PROJ_ID);
	//get share memory
	int shmid = shmget(key,4096,IPC_CREAT | IPC_EXCL | 0644);
	if(shmid < 0)
	{
		perror("shmget error\n");
		exit(0);
	}

	//make relation with share-memory
	char* msm = shmat(shmid,NULL,0);
	int i = 0;
	while(i++<=26)
	{
		printf("client# %s\n",msm);
		sleep(1);
	}
	
	//cut relation
	shmdt(msm);
	sleep(2);

	//free share-memory
	shmctl(shmid,IPC_RMID,NULL);
}
