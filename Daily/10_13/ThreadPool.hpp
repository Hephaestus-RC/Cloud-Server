#pragma once

#include<iostream>
#include<string>
#include<queue>
#include<map>
#include<pthread.h>

using namespace std;

map<string,string> dict = {
	{"apple","pg"},
	{"banana","xj"},
	{"orange","jz"}
};

class Task
{
	private:
		int fd;
	public:
		Task(int _fd)
			:fd(_fd)
		{}
		void Run()
		{
			string key;
			char buf[1024];
			ssize_t s = recv(fd,buf,sizeof(buf)-1,0);
			if(s > 0)
			{
				buf[s] = 0;
				key = buf;
			}

			string value ;
			auto it = dict.find(key);
			if(it != dict.end())
			{
				//error :value = *it;
				value = it->second;
			}
			else
			{
				value = "unkown";
			}
			send(fd,value.c_str(),value.size(),0);
			close(fd);
			
		}
		~Task()
		{}
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
		bool IsEmpty()
		{
			return q.size() == 0;
		}
		void ThreadWait()
		{
			pthread_cond_wait(&cond,&lock);
		}
		void ThreadSignal()
		{
			pthread_cond_signal(&cond);
		}
	public:
		ThreadPool(int _num = 5)
			:num(_num)
		{
			pthread_mutex_init(&lock,nullptr);
			pthread_cond_init(&cond,nullptr);
		}
		void PushTask(Task& t)
		{
			LockQueue();
			q.push(t);
			UnLockQueue();
			ThreadSignal();//signal to one thread;
		}
		Task PopTask()
		{
			Task t = q.front();
			q.pop();
			return t;
		}
		static void* Routine(void * s)
		{
			ThreadPool* self = (ThreadPool*)s;
			pthread_detach(pthread_self());

			for(;;)
			{
				//lock;
				self->LockQueue();
				while(self->IsEmpty())
				{
					self->ThreadWait();
				}
				Task t = self->PopTask();
				//unlock;
				self->UnLockQueue();
				t.Run();
			}
		}
		void InitPool()
		{
			pthread_t tid;
			for(auto i = 0;i<num;++i)
			{
				pthread_create(&tid,nullptr,Routine,(void*)this);
			}
		}
		~ThreadPool()
		{
			pthread_mutex_destroy(&lock);
			pthread_cond_destroy(&cond);
		}
};
