#include<iostream>
#include<queue>
#include<pthread.h>
#include<stdlib.h>

using namespace std;

class Task
{
	private:
		int x;
		int y;
	public:
		Task(int _x,int _y):x(_x),y(_y)
		{}
		int Run()
		{
			return x+y;
		}
		~Task()
		{}

};
class ThreadPool
{
	private:
		int num;
		pthread_mutex_t lock;
		pthread_cond_t cond;
		queue<Task> q;
	private:
		void LockQueue()
		{
			pthread_mutex_lock(&lock);
		}
		void UnLockQueue()
		{
			pthread_mutex_unlock(&lock);
		}
		bool IsQueueEmpty()
		{
			return q.size()==0 ? true : false;
		}
		void ThreadWait()
		{
			pthread_cond_wait(&cond,&lock);
		}
		void NotifyThread()
		{
			pthread_cond_signal(&cond);
		}
		void PushTask(Task& t)
		{
			q.push(t);
		}
		void PopTask(Task& t)
		{
			t = q.front();
			q.pop();
		}
	public:
		ThreadPool(int _num = 5):num(_num)
		{
			cout<<"ThreadPool()"<<endl;
			pthread_mutex_init(&lock,NULL);
			pthread_cond_init(&cond,NULL);
		}
		//Becuse Handler-function is a callback function ,so Handler should to  defined static
		static void* Handler(void* args)
		{
			cout<<"ThreadPool::Hanlder"<<endl;
			pthread_detach(pthread_self());
			ThreadPool* tp = (ThreadPool*)args;
			tp->LockQueue();
			if(tp->IsQueueEmpty())
			{
				tp->ThreadWait();
			}
			Task t(0,0);
			tp->PopTask(t);
			tp->UnLockQueue();
			int result = t.Run();
			cout<<"Thread : "<<pthread_self()<<"result : "<<result<<endl;
		}
		void InitPool()
		{
			cout<<"ThreadPool::InitPool()"<<endl;
			pthread_t tid;
			for(int i = 0;i<num;++i)
			{
				pthread_create(&tid,NULL,Handler,(void*)this);
				//Because Handler-function is static-function ,so we call member-function need "this"point in Handle-function
			}
		}
		void AddTask(Task& t)
		{
			cout<<"ThreadPool::AddTask()"<<endl;
			LockQueue();
			PushTask(t);
			NotifyThread();
			UnLockQueue();
		}
		~ThreadPool()
		{
			cout<<"~ThreadPool()"<<endl;
			pthread_mutex_destroy(&lock);
			pthread_cond_destroy(&cond);
		}
};

int main()
{
	ThreadPool* tp = new ThreadPool(5);
	int count=0;
	tp->InitPool();
	for(;;)
	{
		int x = count%1000+100;
		int y = count%2000+200;
		count++;
		Task t(x,y);
		tp->AddTask(t);
	}
	delete tp;
	return 0;
}
