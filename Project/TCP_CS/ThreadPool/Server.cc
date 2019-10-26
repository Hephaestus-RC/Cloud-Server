#include"tcpServer.hpp"

void Usage(char* args)
{
	cout<<args<<"PORT"<<endl;
}

int main(int argc,char* argv[])
{
	if(argc != 2)
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
