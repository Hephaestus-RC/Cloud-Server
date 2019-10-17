#include"tcpServer.hpp"

int main()
{
	Server* s = new Server();
	s->InitServer();
	s->Start();
	delete s;
	return 0;
}
