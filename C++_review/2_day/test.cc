#include<iostream>
using namespace std;

class A 
{
	public:
		void PrintA()
		{
			cout<<_a<<endl;
		}
		void Show()
		{
			cout<<"A::show"<<endl;
		}
	private:
		int _a;
};

int main()
{
	A* p = nullptr;
	p->PrintA();
	p->Show();
	return 0;
}
