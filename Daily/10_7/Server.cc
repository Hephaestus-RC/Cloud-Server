#include"udpServer.hpp"

void Usage(char* buf)
{
	cout<<buf<<"IP PORT"<<endl;
}
int main(int args,char* argv[])
{
	if(args<3)
	{
		Usage(argv[0]);
		exit(1);
	}
	Server* s = new Server(argv[1],atoi(argv[2]));
	s->InitServer();
	s->Start();
	return 0;
}
