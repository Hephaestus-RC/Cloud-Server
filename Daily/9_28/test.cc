#include<iostream>
using namespace std;


class Test
{
	private:
		int a = 0;
	private:
		int GetA()
		{
			return a;
		}
	public:
		static void Handler(void* args)
		{
			Test* t = (Test*)args;
			cout<<"GetA()"<<t->GetA()<<endl;
			cout<<t->a<<endl;
		}
};
int main()
{
	Test* t = new Test;
	Test::Handler((void*) t);
	delete t;
	return 0;
}
