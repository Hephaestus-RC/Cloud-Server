#include"tcpClient.hpp"

void Usage(string proc)
{
	cout<<proc<<"IP : PORT"<<endl;
}
int main(int args,char* argv[])
{
	if(args < 3)
	{
		Usage(argv[0]);
		exit(1);
	}
	Client* s = new Client(argv[1],atoi(argv[2]));
	s->InitClient();
	s->Run();
	delete s;
	return 0;
}
