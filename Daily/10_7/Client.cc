#include"udpClient.hpp"

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
	Client* s = new Client(argv[1],atoi(argv[2]));
	s->InitClient();
	s->Run();
	return 0;
}
