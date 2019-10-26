#pragma once

#include<iostream>
#include<unistd.h>
#include<stdlib.h>
#include<queue>
#include<map>
#include<string>
#include<cstring>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<pthread.h>

using namespace  std;

map<string,string> dict{
	{"apple","苹果"},
	{"banana","香蕉"},
	{"orange","橘子"}
};

class Task
{
	private:
		int  fd;
	public:
		Task(int _fd)
			:fd(_fd)
		{}
		void Run()
		{ 
			string world;
			string value;
			char buf[1024];
			for(;;)
			{
				int s = recv(fd,buf,sizeof(buf-1),0);
				if(s > 0)
				{
					buf[s] = 0;
					if(buf == "quit")
						break;
					world = buf;	
					auto it = dict.find(world);
					if(it != dict.end())
					{	
						value = it->second;
					}
					else
					{	
						value = "unkown";
					}
					send(fd,value.c_str(),value.size(),0);
				}
				else if (s == 0)
				{
					cout<<"client quit..."<<endl;
					break;
				}
				else
					break;
			}
			close(fd);
		}
		~Task(){}
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
		void ThreadWait()
		{
			pthread_cond_wait(&cond,&lock);
		}
		void ThreadSignal()
		{
			pthread_cond_signal(&cond);
		}
		bool IsEmpty()
		{
			return q.size() == 0;
		}
	public:
		ThreadPool(int _num = 5)
			:num(_num)
		{
			pthread_mutex_init(&lock,nullptr);
			pthread_cond_init(&cond,nullptr);
		}
		static void* Routine(void* args)
		{
			pthread_detach(pthread_self());
			ThreadPool* self = (ThreadPool*)args;
			for(;;)
			{
				self->LockQueue();
				while(self->IsEmpty())
				{
					self->ThreadWait();
				}
				Task t = self->PopTask();
				self->UnLockQueue();
				t.Run();
			}
		}
		void InitThreadPool()
		{
			pthread_t tid;
			for(int i = 0;i<num;++i)
				pthread_create(&tid,nullptr,Routine,(void*)this);
		}
		void PushTask(Task& t)
		{
			LockQueue();
			q.push(t);
			UnLockQueue();
			ThreadSignal();
		}
		Task PopTask()
		{
			Task t = q.front();
			q.pop();
			return t;
		}
		~ThreadPool()
		{
			pthread_mutex_destroy(&lock);
			pthread_cond_destroy(&cond);
		}
};
