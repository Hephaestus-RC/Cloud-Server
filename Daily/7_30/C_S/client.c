#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>

#define PATH "."
#define PROJ_ID 0x6666

int main()
{
	key_t key = ftok(PATH,PROJ_ID);
	if(key < 0)
	{
		perror("server ftok error\n");
		exit(0);
	}
	int shmid = shmget(key,4096,IPC_CREAT);
	if(shmid < 0)
	{
		perror("client shmget error\n");
		exit(1);
	}
	char* buf = shmat(shmid,NULL,0);
	int i = 0;
	while(i<=26)
	{
		buf[i] = 'A'+i;
		i++;
		buf[i] = '0';
		sleep(1);
	}
	shmdt(buf);
    
	return 0;

}
