#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<pthread.h>

using namespace std;

void Usage(char* args)
{
	cout<<args <<" PORT"<<endl;
}
void* Routine(void* args)
{
	pthread_detach(pthread_self());
	int sock = *(int*)args;
	delete args;

	string buf={"<h1>Hello RC</h1>"};
	send(sock,buf.c_str(),buf.size(),0);
	close(sock);
}
int main(int args,char* argv[])
{
	if(args != 2)
	{
		Usage(argv[1]);
		return 1;
	}

	//1.socket
	int listen_sock = socket(AF_INET,SOCK_STREAM,0);
	if(listen_sock < 0)
	{
		cerr<<"socket error"<<endl;
		return 2;
	}
	cout<<"sock success!"<<endl;


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
	cout<<"listen success!"<<endl;

	//4.accept
	struct sockaddr_in peer;
	socklen_t len = sizeof(peer);
	for(;;)
	{
		int sock = accept(listen_sock,(struct sockaddr*)&peer,&len);
		if(sock < 0)
		{
			cout<<"accept error"<<endl;
			continue;
		}
		cout<<"Get New Clinet"<<endl;
		int * s = new int(sock);
		pthread_t tid;
		pthread_create(&tid,nullptr,Routine,s);	
	}

	return 0;
}
