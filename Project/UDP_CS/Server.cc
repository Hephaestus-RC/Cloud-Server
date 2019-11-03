#include"udpServer.hpp"

void Usage(string buf)
{
	cout<<buf<<" IP PORT"<<endl;
}
int main(int argv,char* args[])
{
	if(argv != 3)
	{
		Usage(args[0]);
		exit(1);
	}
	Server* s = new Server(args[1],atoi(args[2]));
	s->InitServer();
	s->Start();
	delete s;
	return 0;
}
