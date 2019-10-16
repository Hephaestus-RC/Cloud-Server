#include<iostream>
using namespace std;

class Empty
{
};

class A 
{
	public:
		void PrintA()
		{
			cout<<_a<<endl;
		}
	private:
		int _a;
};

class B
{
	private:
		char _b;
		double _c;
};
int main()
{
	Empty e;
	A a;
	B b;
	cout<<sizeof(e)<<endl;
	cout<<sizeof(a)<<endl;
	cout<<sizeof(b)<<endl;
	return 0;
}
