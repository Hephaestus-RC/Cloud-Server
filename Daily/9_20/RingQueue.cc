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
	private:
		void P(sem_t& sem)
		{
			sem_wait(&sem);
		}
		void V(sem_t& sem)
		{
			sem_post(&sem);
		}
	public:
		RingQueue(int _cap = 8)
			:cap(_cap)
			 ,array(_cap)
		{
			sem_init(&sem_blank,0,cap);
			sem_init(&sem_data,0,0);
			c_step = 0;
			p_step = 0;
		}
		void PushData(const int& data)
		{
			P(sem_blank);//P
			array[p_step] = data;
			p_step++;
			p_step %= cap;
			V(sem_data);//V
			cout<<"Produce data is "<<data<<endl;
		}
		void PopData()
		{
			int data;
			P(sem_data);
			data = array[c_step];
			c_step++;
			c_step %= cap;
			V(sem_blank);
			cout<<"Consume data is "<<data<<endl;
		}
		~RingQueue()
		{
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
	pthread_t p,c;
	pthread_create(&p,NULL,Producer,(void*)&rq);
	pthread_create(&c,NULL,Consumer,(void*)&rq);

	pthread_join(p,NULL);
	pthread_join(c,NULL);
	return 0;
}
