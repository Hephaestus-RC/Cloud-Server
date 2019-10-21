#include<iostream>
#include<string>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<pthread.h>

using namespace std;
void* Routine(void* args)
{
	pthread_detach(pthread_self());
	int* p = (int*)args;
	int sock = *p;
	delete p;
	
	char buf[10240];
	for(;;)
	{
		int s = recv(sock,buf,sizeof(buf)-1,0);
		if(s > 0)
		{
			buf[s] = 0;
			cout<<"------------------------------------------------------------------"<<endl;
			cout<<buf<<endl;
			cout<<"------------------------------------------------------------------"<<endl;
			
			string response = {"HTTP/1.0 200 OK\r\n\r\n<html><h1>Hello RC</h1></html>"};
			send(sock,response.c_str(),response.size(),0);
		}
		else if(s == 0)
		{
			cout<<"Client Quit..."<<endl;
			break;
		}
		else
			break;
	}
	close(sock);
}

int main(int args,char* argv[])
{
	if(args != 2)
	{
		cout<<argv[0]<<" PORT"<<endl;
		return 1;
	}
	
	//1.socket
	int listen_sock = socket(AF_INET,SOCK_STREAM,0);
	if(listen_sock < 0)
	{
		cerr<<"socket error"<<endl;
		return 2;
	}
	cout<<"socket success!"<<endl;

	//2.bind
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(atoi(argv[1]));
	local.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(listen_sock,(struct sockaddr*)&local,sizeof(local))<0)
	{
		cerr<<"bind error"<<endl;
		return 3;
	}
	cout<<"bind success!"<<endl;

	//3.listen
	if(listen(listen_sock,5)<0)
	{
		cerr<<"listen error"<<endl;
		return 4;
	}
	cout<<"listen success！"<<endl;

	struct sockaddr_in peer;
	for(;;)
	{
		socklen_t len = sizeof(peer);
		int sock = accept(listen_sock,(struct sockaddr*)&peer,&len);
		if(sock < 0)
		{
			cerr<<"accept error"<<endl;
			continue;
		}
		cout<<"Get A New Client"<<endl;
		int* s = new int(sock);
		pthread_t tid;
		pthread_create(&tid,nullptr,Routine,s);
	}
	return 0;
}
