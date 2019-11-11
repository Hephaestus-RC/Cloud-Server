#include"epoll.hpp"

int main(int args,char* argv[])
{
	if(args!=2)
	{
		cout<<"Usage:"<<argv[0]<<" PORT"<<endl;
		exit(1);
	}
	Server* s = new Server(atoi(argv[1]));
	s->InitServer();
	s->Run();
	delete s;
	return 0;
}
