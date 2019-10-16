#include<iostream>
using namespace std;

//void test_auto(int& array[])
//{
//	for(auto& e: array)
//	{
//		cout<<e<<endl;
//	}
//}
int main()
{
	int array[10];
	for(auto &e: array)
	{
		e = 1;
	}
//	test_auto(array);
//	for(auto& e:array)
//	{
//		cout<<e<<endl;
//	}


#if 0
	int a = 10;
	int& ra = a;
	cout<<&a<<endl;
	cout<<&ra<<endl;
#endif
	return 0;
}
//
//int& testfun(int& x)
//{
//	x+=1;
//	return x;
//}
//

#if 0
int main()
{
	const int a = 1;
	const int& ra = a;

	const int& b = 1;

	double d = 12.34;
	const int& rd = d;
	
	int c = 1;
	cout<<testfun(c)<<endl;
	return 0;
}

#endif

//#include<iostream>
//using namespace std;
//
////void Testfun(int a = 1,int b = 2,int c =  3)
////{
////	cout<<a<<endl;
////	cout<<b<<endl;
////	cout<<c<<endl;
////}
//
//int Add(int a,int b)
//{
//	return a+b;
//}
//int Add(int a = 1,int b = 2)
//{
//	return a+b;
//}
////double Add(int a,int b)
////{
////	return a+b;
////}
//
//double Add(double a,double b)
//{
//	return a+b;
//}
//double Add(int a,double b)
//{
//	return a+b;
//}
//
//int main()
//{
//	//Testfun(1,2,3);
//	int a1 = 1,a2 = 2;
//	double d1 = 3.0,d2 = 4.0;
//	cout<<Add(a1,a2)<<endl;
//	cout<<Add(d1,d2)<<endl;
//	cout<<Add(a1,d2)<<endl;
//	return 0;
//}

