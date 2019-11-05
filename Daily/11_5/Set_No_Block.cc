#include<iostream>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/socket.h>

using namespace std;

void SetNoBlock(int fd)
{
	int f = fcntl(fd,F_GETFL);
	if(f < 0)
	{
		cerr<<"error!"<<endl;
		exit(0);
	}
	fcntl(fd,F_SETFL,f | O_NONBLOCK);
}
int main()
{
	SetNoBlock(0);
	while(1)
	{
		char buf[1024] = {0};
		sleep(2);
		ssize_t s = read(0,(void*)buf,sizeof(buf)-1);

		if(s < 0)
		{
			cerr<<"recv error"<<endl;
			continue;
		}
		else if(s == 0)
		{
			cout<<"recv end!"<<endl;
			break;
		}
		else
		{
			buf[s] = 0;
			cout<<"Get :"<<buf<<endl;
		}
	}
	return 0;
}
