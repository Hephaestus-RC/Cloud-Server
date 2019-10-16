#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<unistd.h>
#include<stdlib.h>

#define PATH "."
#define PROJ_ID 0X6666

int main()
{
	key_t key = ftok(PATH,PROJ_ID);
	if(key < 0)
	{
		perror("ftok error\n");
		exit(0);
	}
	//
	int shmid = shmget(key,4096,IPC_CREAT);
	if(shmid < 0)
	{
		perror("shmget error\n");
		exit(1);
	}
	//make connect
	char* addr =  shmat(shmid,NULL,0);

	int i = 0;
	while(i<=26)
	{
		addr[i] = 'A'+i;
		i++;
		addr[i] = 0;
		sleep(1);
	}
	
	shmdt(addr);
	sleep(2);
	return 0;
}
