#include"udpServer.hpp"
#include<iostream>

int main()
{
	Server* s = new Server;
	s->Init();
	s->Start();
	return 0;
}
