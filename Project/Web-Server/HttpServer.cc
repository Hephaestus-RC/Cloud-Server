#include"HttpServer.hpp"

void Usage(string proc)
{
	cout<<"Usage: "<<proc<<" PORT "<<endl;
}
int main(int args,char* argv[])
{
	if(args!=2)
	{
		Usage(argv[0]);
		exit(1);
	}
	HttpServer* hs = new HttpServer(atoi(argv[1]));
	hs->InitHttpServer();
	hs->Start();

	delete hs;

	return 0;
}
