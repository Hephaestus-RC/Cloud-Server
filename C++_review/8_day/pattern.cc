#include<iostream>
using namespace std;

class singleton1
{
	public:
		static singleton1* GetInstance()
		{
			return &m_instance;
		}

	private:
		singleton1(){};
		singleton1(const singleton1&) = delete;
		singleton1& operator=(const singleton1& s) = delete;
		static singleton1 m_instance;
};
singleton1 singleton1::m_instance;

int main()
{
	//singleton1* s1 = GetInstance();
	return 0;
}
