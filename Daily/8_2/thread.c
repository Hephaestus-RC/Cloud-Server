#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>

int getret = 11;
void* pthread_routins(void* argv)
{
	printf("New 1 thread tid : %lu\n",pthread_self());
	while(1)
	{
		printf("This is new thread !\n");
		sleep(1);
		break;
	}
	//return (void*)11;
	pthread_exit((void*)&getret);
}
int main()
{
	printf("Main thread tid : %lu\n",pthread_self());
	pthread_t tid;
	pthread_create(&tid,NULL,pthread_routins,NULL);
	void* ret;
	if(pthread_join(tid,&ret) != 0)
		printf("new thread exit !\n");
	else
		printf("new thread return code : %d\n",ret);

	return 0;
}	
