#include<iostream>
using namespace std;

template <class T>
T Add(const T& left,const T& right)
{
	cout<<"template function() : "<<endl;
	return left+right;
}

int Add(const int& left,const int& right)
{
	cout<<"int function() : "<<endl;
	return left + right;
}

//double Add(const double& left,const double& right)
//{
//	cout<<"double function() : "<<endl;
//	return left + right;
//}
int main()
{
	int a1 = 10, a2 = 20;
	double d1 = 10.0,d2 = 20.0;
	cout<<Add(a1,a2)<<endl;
	cout<<Add(d1,d2)<<endl;
	cout<<Add(a1,(int)d1)<<endl;

	cout<<Add<int>(a1,d1)<<endl;
	return 0;
}
