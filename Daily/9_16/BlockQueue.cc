#include<iostream>
#include<queue>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>

using namespace std;

pthread_mutex_t lock;
pthread_cond_t c_cond;
pthread_cond_t p_cond;

class BQueue
{
	private:
		queue<int> q;
		int _cap;
	private:
		bool  IsFull()
		{
			return (q.size() == _cap);
		}
		bool IsEmpty()
		{
			return  (q.size() == 0);
		}
		void SignalProduc()
		{
			pthread_cond_signal(&p_cond);
		}
		void SignalConsumer()
		{
			pthread_cond_signal(&c_cond);
		}
		void WaitProduc()
		{
			pthread_cond_wait(&p_cond,&lock);
		}
		void WaitConsumer()
		{
			pthread_cond_wait(&c_cond,&lock);
		}
	public:
		BQueue(int cap = 5)
		{
			_cap = cap;
			pthread_mutex_init(&lock,NULL);
			pthread_cond_init(&c_cond,NULL);
			pthread_cond_init(&p_cond,NULL);
		}
		//producer
		void PushData(int data)
		{
			pthread_mutex_lock(&lock);
			if(IsFull())
			{
				cout<<"BlockQueue is full , signal to Producer"<<endl;
				SignalConsumer();
				WaitProduc();
			}
			pthread_mutex_unlock(&lock);
			q.push(data);
		}
		//consumer
		int PopData()
		{
			pthread_mutex_lock(&lock);
			if(IsEmpty())
			{
				cout<<"BlockQueue is empty, signal to Consumer"<<endl;
				SignalProduc();
				WaitConsumer();
			}
			pthread_mutex_unlock(&lock);
			int ret = q.front();
			q.pop();
			return ret;
		}
		~BQueue()
		{
			_cap = 0;
			pthread_mutex_destroy(&lock);
			pthread_cond_destroy(&c_cond);
			pthread_cond_destroy(&p_cond);
		}
};

void* Producer(void* arg)
{
	BQueue* bq = (BQueue*)arg;
	while(1)
	{
		int x = rand()%100+1;
		cout<<"Produc data is :"<<x<<endl;
		bq->PushData(x);
	}
	//return nullptr;
}
void* Consumer(void* arg)
{
	BQueue* bq = (BQueue*)arg;
	int x = 0;
	while(1)
	{
		usleep(100000);
		x = bq->PopData();
		cout<<"Consume data is :"<<x<<endl;
	}
	//return nullptr;
}
int main()
{
	BQueue bq;
	pthread_t t1,t2;

	pthread_create(&t1,NULL,Producer,(void*)&bq);
	pthread_create(&t2,NULL,Consumer,(void*)&bq);

	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
}
