#include"udpClient.hpp"

void Usage(char* buf)
{
	cout<<buf<<" SERVER_IP SERVER_PORT"<<endl;
}

// ./client 127.0.0.1 8080
int main(int argv,char* args[])
{
	if(argv != 3)
	{
		Usage(args[0]);
		exit(1);
	}
	Client* c = new Client(args[1],atoi(args[2]));
	c->InitClient();
	c->Run();
	delete c;
	return 0;
}
