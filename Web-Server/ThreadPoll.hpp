#pragma once 
#include<iostream>
#include<queue>
#include<pthread.h>
#include<unistd.h>
using namespace std;

typedef void(*handler_t)(int);

class Task
{
    private:
        int sock;
        handler_t handler; 
    public:
        Task(int _sock ,handler_t _handler):sock(_sock),handler(_handler)
        {}
        void Run()
        {
            handler(sock);
        }
        ~Task()
        {
            //这里不可以close(sock)，如果这里关闭了套接字，将会导致服务器异常
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
        void ThreadWait()
        {
            pthread_cond_wait(&cond,&lock);
        }
        void ThreadSignal()
        {
            pthread_cond_signal(&cond);
        }
    public:
        ThreadPool(int _num = 5):num(_num)
        {
            pthread_mutex_init(&lock,nullptr);
            pthread_cond_init(&cond,nullptr);
        }
        static void* Routine(void* args)
        {
            pthread_detach(pthread_self());
            ThreadPool* tp = (ThreadPool*)args;
            for(;;)
            {
                tp->LockQueue();
                while(tp->IsEmpty())
                    tp->ThreadWait();
                Task t = tp->PopTask();
                tp->UnLockQueue();
                t.Run();
            }
        }
        void InitThreadPool()
        {
            pthread_t tid;
            for(int i = 0; i<num ;++i)
                pthread_create(&tid,nullptr,Routine,this);
        }
        bool IsEmpty()
        {
            return q.empty();
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

//单例模式
class Singleton
{
    private:
        static ThreadPool* tp;
        static pthread_mutex_t lock;
    public:
        static ThreadPool* GetInstance()
        {
            if(tp==nullptr)
            {
                pthread_mutex_lock(&lock);
                if(tp == nullptr)
                {
                    tp = new ThreadPool(8);
                    tp->InitThreadPool();
                }
                pthread_mutex_unlock(&lock);
            }
            return tp;
        }
};

ThreadPool* Singleton::tp = nullptr;
pthread_mutex_t Singleton::lock = PTHREAD_MUTEX_INITIALIZER;
