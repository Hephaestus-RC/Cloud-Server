#include<iostream>
#include<string>
#include<poll.h>
using namespace std;

int main()
{
	struct pollfd rfds[1024];
	rfds[0].fd = 0;
	//设置读事件检测
	rfds[0].events = POLLIN;
	//设置写事件检测
	rfds[0].events |= POLLOUT;
	rfds[0].revents = 0;

	string buf;
	while(1)
	{
		switch(poll(rfds,1,-1))
		{
			case 0:
				cout<<"Time out..."<<endl;
				break;
			case -1:
				cout<<"poll error..."<<endl;
				break;
			default:
				for(int i = 0 ;i < 1024;i++)
				{

					if(rfds[i].revents & POLLIN)
					{
						cin>>buf;
						cout<<"echo# "<<buf<<endl;
					}
					else if(rfds[0].revents & POLLOUT)
						cout<<buf<<endl;
				}
				break;
		}
	}
	return 0;
}
