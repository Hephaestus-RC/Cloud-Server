#include"tcpClient.hpp"

void Usage(char* args)
{
	cout<<args<<"IP : PORT"<<endl;
}
int main(int argc,char* argv[])
{
	if(argc != 3)
	{
		Usage(argv[0]);
		exit(1);
	}
	Client* c = new Client(argv[1],atoi(argv[2]));
	c->InitClient();
	c->Run();

	delete c;
	return 0;
}
