#pragma once

#include<iostream>
#include<string>
#include<queue>
#include<pthread.h>
#include<map>

using namespace std;

map<string,string> dict = {
	{"apple","pg"},
	{"banana","xj"},
	{"orange","jz"}
};

class Task
{
	private:	
		string s;
	public:
		Task(string _s)
			:s(_s)
		{}
		void Run(int )
		{
			auto it = dict.find(s);
			if(it != dict.end())
			{
				
			}
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
			pthread_mutex_lcok(&lock);
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
			:num(5)
		{
			pthread_mutex_init(&lock,nullptr);
			pthread_cond_init(&cond,nullptr);
		}
		void PushTask(Task& t)
		{
			LockQueue();
			q.push(t);
			UnLockQueue();
			ThreadSignal();
		}

		void PopTask()
		
		{
			LockQueue();
			if(IsEmpty())
			{
				ThreadWait();
			}
			Task t = q.fron();
			q.pop();
			UnLockQueue();
			t.Run();
		}
		~ThreadPool()
		{
			pthread_mutex_destroy(&lock);
			pthread_cond_destroy(&cond);
		}

};
