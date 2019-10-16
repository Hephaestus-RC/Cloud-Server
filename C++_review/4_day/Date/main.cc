#include"Date.hpp"
#include<iostream>
using namespace std;

int main()
{
	Date d1;
	Date d2(2019,8,15);
	Date d3(d2);
	
	d1.Display();
	d2.Display();
	d3.Display();
	
	d1++;
	d2++;
	d3++;
	
	d1.Display();
	d2.Display();
	d3.Display();
	
	cout<<(d1 == d2)<<endl;
	cout<<(d2 == d3)<<endl;
	
	d1+100;
	d2+100;
	d3+100;
	
	d1.Display();
	d2.Display();
	d3.Display();

	return 0;
}
