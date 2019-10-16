#include<iostream>
using namespace std;

#if 0
class A
{
	public:
		A(int a)
			:_a(a)
		{

		}
	private:
		int _a;
};
class B
{
	public:
		B(int a,int ref)
			:_aobj(a)
			,_ref(ref)
			,_n(10) 
		{
			//_a = 1;
			//_ref = 2;

		}
	private:
		A _aobj;
		int& _ref;
		const int _n;
};
#endif
//----------------------explicit
class Date
{
	public:
	//	Date(int y)
	//		:_year(y)
	//	{}
	Date(int year)
			:_year(year)
		{

		}
	private:
		int _year;
		int _month;
		int _day;
};
class C
{
	public:
		C()
		{
			++_count;	
		}
		C(const C& t)
		{
			++_count;
		}
	    static int GetACount()
		{
			return _count;
		}
	private:
		static int _count;
};
int C::_count = 0;

class Test
{
	public:
		void Display()
		{
			cout<<a<<" "<<b<<endl;
		}
	private:
		int a = 10;
		int  b = 20;

};
int main()
{
	//Date d1(2019);
	//d1 = 2020;
	//cout<<C::GetACount()<<endl;
	//C c1,c2;
	//C c3(c2);
	//cout<<C::GetACount()<<endl;
	Test t;
	t.Display();

	return 0;
}
