#include""ThreadPool.hpp"
#include<iostream>
#include<unistd.h>

using namespace std;

int main()
{
	ThreadPool tp = new ThreadPool ;
	tp->InitThread();
	int count;
	while(1)
	{
		int x =  count % 1000 +100;
		int y = count % 2000 +300;
		count++;
		Task t(x,y);
		tp->AddTask(t);
		sleep(1);
	}
	delete tp;

	return 0;
}
