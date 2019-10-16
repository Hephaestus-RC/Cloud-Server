#include<iostream>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<queue>
#include<assert.h>
#include<time.h>
using namespace std;

class BlockQueue
{
	private:
		queue<int> q;
		pthread_mutex_t lock;
		pthread_cond_t cond;
	private:
		void LockQueue()
		{
			pthread_mutex_lock(&lock);
		}
		void UnlockQueue()
		{
			pthread_mutex_unlock();
		}
		bool IsEmpty()
		{
			return q.size()==0?true:false;
		}
		void WakeUpOneThread()
		{
			pthread_cond_signal(*cond);
		}
		void ThreadWait()
		{
			pthread_cond_wait(&cond,&lock);
		}
		//void UpdataWaterline()
		//{
		//}
	public:
		BlockQueue()
		{
			pthread_mutex_init(&lock,NULL);
			pthread_cond_init(&cond,NULL);
		}
		void PushData(const int& data)
		{
			cout<<"Push data is "<<data<<endl;
			LockQueue();
			q.push(data);
			WakeUpOneThread();
			UnlockQueue();
		}
		void  PopData()
		{
			LockQueue();
			while(IsEmpty())
			{
				Threadwait();
			}
			int p = q.front();
			q.pop();
			UnlockQueue();
			cout<<"Pop Data is : "<<p<<endl;
		}
		~BlockQueue()
		{
			pthread_mutex_destroy(&lock);
			pthread_cond_destroy(&cond);
		}
}

void* product(void* args)
{
	BlockQueue* bp = (BlockQueue* )args;
	srand((unsigned long)time(NULL));
	while(1)
	{
		int data = rand()%100+1;
		bp->PushQueue(data);	
	}
}
void* consume(void* args)
{
	BlockQueue* bp = (BlockQueue*)args;
	while(1)
	{
		bp->PopData();
	}
}
int main()
{
	BlockQueue bp;
	pthread_t p,c;
	pthread_create(&p,NULL,product,(void*)&bp);
	pthread_create(&c,NULL,consume,(void*)&bp);

	pthread_join(&p);
	pthread_join(&c);

	return 0;
}
