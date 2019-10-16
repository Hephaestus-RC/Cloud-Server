#include<iostream>
#include<pthread.h>
#include<unistd.h>
#include<queue>

using namespace std;

int main();

class Task
{
	private:
		int x;
		int y;
	public:
		Task(int _a = 1,int _b = 1):x(_a),y(_b){}
		~Task(){}
		int Run()
		{
			return x+y;	
		}
};

class ThreadPool
{
	private:
		int num;
		queue<Task> q;
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
		bool IsQueueEmpty()
		{
			return (q.size() == 0 ? true : false);
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
		void ThreadWait()
		{
			pthread_cond_wait(&cond,&lock);
		}
		void NotifyThread()
		{
			pthread_cond_signal(&cond);
		}
	public:
		ThreadPool(int _num = 6):num(_num)
		{
			pthread_mutex_init(&lock,NULL);
			pthread_cond_init(&cond,NULL);
		}
		~ThreadPool()
		{
			pthread_mutex_destroy(&lock);
			pthread_cond_destroy(&cond);
		}
		static void* HandlerTask(void* args)
		{
			pthread_detach(pthread_self());
			ThreadPool* tp = (ThreadPool*)args;
			while(1)
			{
				tp->LockQueue();
				if(tp->IsQueueEmpty())
				{
					tp->ThreadWait();
				}
				Task t;
				tp->PopTask(t);
				tp->UnLockQueue();
				int result = t.Run();
				cout<<"thread : "<<pthread_self()<<"result : "<<result<<endl;
			}
		}
		void InitThreadPool()
		{
			int i = 0;
			for(;i<num;i++)
			{
				pthread_t tid;
				pthread_create(&tid,NULL,HandlerTask,(void*)this);
			}
		}
		void AddTask(Task& t)
		{
			LockQueue();
			PushTask(t);
			UnLockQueue();
			NotifyThread();
		}
};


int main()
{
	ThreadPool* tp = new ThreadPool();
	tp->InitThreadPool();
	int count = 0;
	for(int i = 0;i<10;++i)
	{
		int x = count % 1000 + 100;
		int y = count % 2000 + 300;
		Task t(x,y);
		tp->AddTask(t);
	}
	delete tp;
	return 0;
}

