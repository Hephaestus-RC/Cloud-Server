#include<iostream>
#include<pthread.h>
#include<unistd.h>
using namespace std;

int ticket = 100;
pthread_mutex_t lock;

void* BuyTicket(void* args)
{
	while(1)
	{
		pthread_mutex_lock(&lock);
		if(ticket > 0)
		{
			cout<<"Buy one ticket , ticket : "<<ticket--<<endl;
			pthread_mutex_unlock(&lock);
		}
		else
		{
			pthread_mutex_unlock(&lock);
			break;
		}
	}
	cout<<"ticket is over , "<<(char*)args<<endl;
}

int main()
{
	pthread_mutex_init(&lock,NULL);
	pthread_t tid[5];

	pthread_create(tid+0,NULL,BuyTicket,(void*)"thread 1");
	pthread_create(tid+1,NULL,BuyTicket,(void*)"thread 2");
	pthread_create(tid+2,NULL,BuyTicket,(void*)"thread 3");
	pthread_create(tid+3,NULL,BuyTicket,(void*)"thread 4");
	pthread_create(tid+4,NULL,BuyTicket,(void*)"thread 5");

	pthread_join(tid[0],NULL);
	pthread_join(tid[1],NULL);
	pthread_join(tid[2],NULL);
	pthread_join(tid[3],NULL);
	pthread_join(tid[4],NULL);
	
	pthread_mutex_destroy(&lock);
	return 0;

}
