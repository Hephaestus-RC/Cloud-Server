#include<iostream>
#include<unistd.h>

using namespace std;

int main()
{
	int a = 0;
	alarm(1);
	while(1)
	{
		a++;
		cout<<a<<endl;
	}
	cout<<a<<endl;

	return 0;
//	int a = 0;
//	int ret = fork();
//	if(ret < 0)
//		cerr<<"frok error!\n"<<endl;
//	else if(ret == 0)
//	{
//		alarm(1);
//		while(1)
//			a++;
//	}
//	cout<<a<<endl;
//	return 0;
}
