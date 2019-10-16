#include"protocol.hpp"
#include<string.h>
#include<pthread.h>

void* Routine(void* args)
{
	pthread_detach(pthread_self());
	int sock = *(int*)args;
	request rp;
	response rsp = {0,0};
	for(;;)
	{
		bzero((void*)&rsp,sizeof(rsp));
		int s = recv(sock,(void*)&rp,sizeof(rp),0);
		if(s > 0)
		{
			switch(rp.op)
			{
				case '+':
					rsp.result = rp.x + rp.y;
					break;
				case '-':
					rsp.result = rp.x - rp.y;
					break;
				case '*':
					rsp.result = rp.x * rp.y;
					break;
				case '/':
					if(rp.y == 0)
					{
						rsp.status = 1;
						break;
					}
					rsp.result = rp.x / rp.y;
					break;
				case '%':
					if(rp.y == 0)
					{
						rsp.status = 2;
						break;
					}
					rsp.result = rp.x % rp.y;
					break;
				default:
					rsp.status = 3;
					break;
			}
			send(sock,(void*)&rsp,sizeof(rsp),0);
		}
		else if(s == 0)
		{
			cout<<"client quit..."<<endl;
			break;
		}
	}
	close(sock);
}
int main()
{
	//1.socket
	int listen_sock = socket(AF_INET,SOCK_STREAM,0);
	if(listen_sock < 0)
	{
		cerr<<"sock error"<<endl;
		exit(1);
	}
	cout<<"sock success!"<<endl;

	//2.bind
	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(8888);
	local.sin_addr.s_addr = htonl(INADDR_ANY);	
	if(bind(listen_sock,(struct sockaddr*)&local,sizeof(local))<0)
	{
		cerr<<"bind error!"<<endl;
		exit(2);
	}
	cout<<"bind success!"<<endl;
	
	//3.listen
	if(listen(listen_sock,5)<0)
	{
		cerr<<"listen error"<<endl;
		exit(3);
	}
	cout<<"listen success!"<<endl;

	//4.accept
	struct sockaddr_in peer;
	for(;;)
	{
		socklen_t len = sizeof(peer);
		int sock = accept(listen_sock,(struct sockaddr*)&peer,&len);
		if(sock < 0)
			continue;
		cout<<"Get New Link..."<<endl;
		pthread_t tid;
		pthread_create(&tid,nullptr,Routine,(void*)&sock);

	}
	return 0;	
}
