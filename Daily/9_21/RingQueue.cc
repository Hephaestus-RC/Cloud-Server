#include<iostream>
#include<stdlib.h>
#include<vector>
#include<semaphore.h>
#include<unistd.h>
#include<pthread.h>
using namespace std;

class RingQueue
{
	private:
		vector<int> array;
		int cap;
		int c_step;
		int p_step;
		sem_t sem_blank;
		sem_t sem_data;
		pthread_mutex_t lock;
	private:
		void P(sem_t& sem)
		{
			sem_wait(&sem);
		}
		void V(sem_t& sem)
		{
			sem_post(&sem);
		}
		void Lock()
		{
			pthread_mutex_lock(&lock);
		}
		void UnLock()
		{
			pthread_mutex_unlock(&lock);
		}
	public:
		RingQueue(int _cap = 8)
			:cap(_cap)
			 ,array(_cap)
		{
			pthread_mutex_init(&lock,NULL);
			sem_init(&sem_blank,0,cap);
			sem_init(&sem_data,0,0);
			c_step = 0;
			p_step = 0;
		}
		void PushData(const int& data)
		{
			Lock();
			P(sem_blank);//P
			array[p_step] = data;
			p_step++;
			p_step %= cap;
			V(sem_data);//V
			UnLock();
			cout<<"pthread is "<<pthread_self()<<"Produce data is "<<data<<endl;
		}
		void PopData()
		{
			int data;
			Lock();
			P(sem_data);
			data = array[c_step];
			c_step++;
			c_step %= cap;
			V(sem_blank);
			UnLock();
			cout<<"pthread is "<<pthread_self()<<" Consume data is "<<data<<endl;
		}
		~RingQueue()
		{
			pthread_mutex_destroy(&lock);
			sem_destroy(&sem_blank);
			sem_destroy(&sem_data);
		}

};
void* Producer(void* arg)
{
	RingQueue* rq = (RingQueue*)arg;
	while(1)
	{
		sleep(1);
		int data = rand()%100+1;
		rq->PushData(data);
	}
}
void* Consumer(void* arg)
{
	RingQueue* rq = (RingQueue*)arg;
	while(1)
	{
		rq->PopData();
	}
}
int main()
{
	srand((unsigned long)time(NULL));
	RingQueue rq(7);
	pthread_t p1,p2,p3,p4,c1,c2,c3,c4;
	pthread_create(&p1,NULL,Producer,(void*)&rq);
	pthread_create(&p2,NULL,Producer,(void*)&rq);
	pthread_create(&p3,NULL,Producer,(void*)&rq);
	pthread_create(&p4,NULL,Producer,(void*)&rq);
	pthread_create(&c1,NULL,Consumer,(void*)&rq);
	pthread_create(&c2,NULL,Consumer,(void*)&rq);
	pthread_create(&c3,NULL,Consumer,(void*)&rq);
	pthread_create(&c4,NULL,Consumer,(void*)&rq);

	pthread_join(p1,NULL);
	pthread_join(p2,NULL);
	pthread_join(p3,NULL);
	pthread_join(p4,NULL);
	pthread_join(c1,NULL);
	pthread_join(c2,NULL);
	pthread_join(c3,NULL);
	pthread_join(c4,NULL);
	return 0;
}
