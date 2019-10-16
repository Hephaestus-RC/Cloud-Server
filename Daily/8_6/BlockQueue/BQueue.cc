#include<iostream>
#include<pthread.h>
#include<unistd.h>
#include<queue>
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
		void UnLockQueue()
		{
			pthread_mutex_unlock(&lock);
		}
		bool IsEmpty()
		{
			return q.size()==0 ? true:false;
		}
		void WakeUpOneThread()
		{
			pthread_cond_signal(&cond);
		}
		void ThreadWait()
		{
			pthread_cond_wait(&cond,&lock);
		}
	public:
		BlockQueue()
		{
			pthread_mutex_init(&lock,nullptr);
			pthread_cond_init(&cond,nullptr);
		}
		~BlockQueue()
		{
			pthread_mutex_destroy(&lock);
			pthread_cond_destroy(&cond);
		}
		void PushData(int& data)
		{
			LockQueue();
			q.push(data);
			UnLockQueue();
			WakeUpOneThread();
		}
		void PopData(int& data)
		{
			LockQueue();
			while(IsEmpty())
				ThreadWait();
			data = q.front();
			q.pop();
			UnLockQueue();
		}

};

void* Product (void* args)
{
	srand((unsigned long)time(NULL));
	BlockQueue* bp = (BlockQueue*)args;
	while(1)
	{
		int data = rand()%100+1;
		bp->PushData(data);
		cout<<"Product Push one : "<<data<<" wake up one thead done..."<<endl;
		sleep(1);
	}
}
void* Consume (void* args)
{
	BlockQueue* bp = (BlockQueue*)args;
	while(1)
	{
		int d;
		bp->PopData(d);
		cout<<"Consume Pop One : "<<d<<endl;
	}
}
int main()
{
	BlockQueue bp;
	pthread_t p,c;
	pthread_create(&p,nullptr,Product,(void*)&bp);
	pthread_create(&c,nullptr,Consume,(void*)&bp);

	pthread_join(p,nullptr);
	pthread_join(c,nullptr);
	
	return 0;
}
























//#include<iostream>
//#include<queue>
//#include<unistd.h>
//#include<pthread.h>
//#include<time.h>
//using namespace std;
//
//class BlockQueue
//{
//	private:
//		queue<int> q;
//		pthread_mutex_t lock;
//		pthread_cond_t cond;
//	public:
//		BlockQueue()
//		{
//			pthread_mutex_init(&lock,nullptr);
//			pthread_cond_init(&cond,nullptr);
//		}
//		~BlockQueue()
//		{
//			pthread_cond_destroy(&cond);
//			pthread_mutex_destroy(&lock);
//		}
//		void Pushdata(int& data)
//		{
//			lockqueue();
//			q.push(data);
//			cout<<"push one : "<<data<<endl;
//			unlockqueue();
//			WakeUpOneThread();
//		}
//		void Popdata()
//		{
//			if(IsEmpty())
//				ThreadWait();
//			lockqueue();
//			int t = q.front();
//			q.pop();
//			cout<<"pop one : "<<t<<endl;
//			unlockqueue();
//		}
//		bool IsEmpty()
//		{
//			return q.size()==0 ? true:false;
//		}
//		void lockqueue()
//		{
//			pthread_mutex_lock(&lock);	
//		}
//		void unlockqueue()
//		{
//			pthread_mutex_unlock(&lock);
//		}
//		void WakeUpOneThread()
//		{
//			pthread_cond_signal(&cond);
//		}
//		void ThreadWait()
//		{
//			pthread_cond_wait(&cond,&lock);
//		}
//};
//void* Producer(void* args)
//{
//	BlockQueue* bp = (BlockQueue*)args;
//	srand((unsigned long)time(NULL));
//	while(1)
//	{
//		int t = rand()%100+1;
//		bp->Pushdata(t);
//		sleep(1);
//	}
//}
//void* Customer(void* args)
//{
//	BlockQueue* bp = (BlockQueue*)args;
//	while(1)
//		bp->Popdata();
//}
//int main()
//{
//	BlockQueue bp;
//	pthread_t p,c;
//	pthread_create(&p,NULL,Producer,(void*)&bp);
//	pthread_create(&c,NULL,Customer,(void*)&bp);
//
//	pthread_join(p,NULL);
//	pthread_join(c,NULL);
//
//	return 0;
//}
