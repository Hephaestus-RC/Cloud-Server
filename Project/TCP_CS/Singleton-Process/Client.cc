#include"tcpClient.hpp"

int main()
{
	Client* s = new Client();
	s->InitClient();
	s->Run();
	delete s;
	return 0;
}
