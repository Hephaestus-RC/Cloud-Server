#include"udpClient.hpp"

void Usage(char* buf)
{
	cout<<"Usage ;"<<buf<<"IP PORT"<<endl;
}

int main(int args,char* argv[])
{
	if(args < 3)
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
