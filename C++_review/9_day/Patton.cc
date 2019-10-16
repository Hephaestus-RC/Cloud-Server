#include<iostream>
using namespace std;

class Singleton1
{
	public:
		static Singleton1* GetInstance()
		{
			return &m_instance;
		}
	private:
		Singleton1(){};
		Singleton1(const Singleton1&) = delete;
		Singleton1& operator=(const Singleton1&) = delete;
		static Singleton1 m_instance;
};
Singleton1  Singleton1::m_instance;

#include<mutex>
#include<thread>

class Singleton2
{
	public:
		static Singleton2* GetInstance()
		{
			if(m_instance)
			{
				m_tx.lock();
				if(m_instance)
				{
					m_instance = new Singleton2();
				}
				m_tx.unlock();
			}
			return m_instance;
		}
		class CGorbar
		{
			public:
				~CGorbar()
				{
					if(Singleton2::m_instance)
						delete m_instance;
				}
		};
		static CGorbar bor;
	private:
		Singleton2(){};
		Singleton2(const Singleton2&) = delete;
		Singleton2& operator=(const Singleton2&) = delete;
		static Singleton2* m_instance;
		static mutex m_tx;
};
Singleton2* Singleton2::m_instance;
mutex Singleton2::m_tx;
Singleton2::CGorbar bor;

int main()
{
	//Singleton1* s1 = GetInstance();

	return 0;
}
