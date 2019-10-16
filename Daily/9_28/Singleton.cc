#include<iostream>
#include<pthread.h>
using namespace std;

//hungry-man version
template<class T>
class Singleton1
{
	private:
		static T data;
	public:
		static T& GetInstance()
		{
			return data;
		}
};
T Singleton1::data = 0;


//idle-man version
template<class T>
class Singleton2
{
	private:
		volatile static T* data;
		static std::mutex lock;
	public:
		static  T* GetInstance()
		{
			if(data == nullptr)
			{
				lock.lock();
				if(data == nullptr)
					data = new T();
				lock.unlock();
			}
			return data;
		}
};


