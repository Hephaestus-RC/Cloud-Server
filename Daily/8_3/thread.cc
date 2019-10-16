#include<iostream>
#include<pthread.h>
#include<cstdlib>
#include<string>
#include<unistd.h>
using namespace std;

void* thread_toutine(void* arg)
{
	cout<<"new thread tid : "<<pthread_self()<<endl;
	//pthread_detach(pthread_self());
	while(1)
	{
		cout<<"this is new thread!"<<endl;
		sleep(1);
		//break;
		pthread_cancel(pthread_self());
	}
	pthread_exit((void*)10);
}

int main()
{
	pthread_t tid;
	cout<<"main tid thread : "<<pthread_self()<<endl;
	pthread_create(&tid,NULL,thread_toutine,NULL);
	sleep(1);
	//void* get;
	//pthread_join(tid,&get);
	//pthread_detach(tid);
	//cout<<"ret : "<<*((int*)&get)<<endl;
	//pthread_cancel(tid);
	while(1)
	{
		cout<<"main thread is running"<<endl;
		sleep(1);
	}

	return 0;
}
