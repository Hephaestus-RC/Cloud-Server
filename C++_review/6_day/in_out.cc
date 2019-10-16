#include<iostream>
using namespace std;

class A
{
	private:
		static int k;
		int h;
	public:
		class B
		{
			public:
				void foo(const A& a)
				{
					cout<<k<<endl;
					cout<<a.h<<endl;
				}
		};
};

int A::k = 1;

int main()
{
	A::B b;
	b.foo(A());

	return 0;
}
