#include"tcpServer.hpp"

void Usage(string proc)
{
	cout<<proc<<" PORT"<<endl;
}
int main(int args,char* argv[])
{
	if(args < 2)
	{
		Usage(argv[0]);
		exit(1);
	}
	Server* s = new Server(atoi(argv[1]));
	s->InitServer();
	s->Start();
	delete s;
	return 0;
}
