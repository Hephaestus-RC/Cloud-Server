#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>

#define PATH "."
#define PROJ_ID 0x6666

int main()
{
	key_t key = ftok(PATH,PROJ_ID);
	int id = shmget(key,4096,IPC_CREAT|IPC_EXCL);
	
	shmat();
	shmdt();

	shmctl(id);
}
