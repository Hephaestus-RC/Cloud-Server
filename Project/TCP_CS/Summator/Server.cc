#include"protocol.hpp"

#include<string.h>

void* Routine(void* args)
{
	pthread_detach(pthread_self());
	int sock = *(int*)args;

	request rq;
	for(;;)
	{
		//bzero((void*)&rsp,sizeof(rsp)); // 当rsp设置在循环外时需要每次运算前将rsp置空
		int s = recv(sock,(void*)&rq,sizeof(rq),0);
		if(s > 0)
		{
			response rsp{0,0};
			switch(rq.op)
			{
				case '+':
					rsp.result = rq.x + rq.y;
					break;
				case '-':
					rsp.result = rq.x - rq.y;
					break;
				case '*':
					rsp.result = rq.x * rq.y;
					break;
				case '/':
					if(rq.y == 0)
					{
						rsp.status = 1;
						break;
					}
					rsp.result = rq.x / rq.y;
					break;
				case '%':
					if(rq.y == 0)
					{
						rsp.status = 2;
						break;
					}
					rsp.result = rq.x % rq.y;
					break;
				default:
					rsp.status = 3;
					break;
			}
			send(sock,(void*)&rsp,sizeof(rsp),0);	
		}
		else if(s == 0)
		{
			//此时client已经退出
			cout<<"Client quit..."<<endl;
			break;
		}
		else
			break;

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
	local.sin_addr.s_addr = htonl(INADDR_ANY); 	   //INADDR_ANY == 0
	if(bind(listen_sock,(struct sockaddr*)&local,sizeof(local)) < 0)
	{
		cerr<<"bind error"<<endl;
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
		if(sock > 0)
		{
			cout<<"		GET New Link..."<<endl;
			pthread_t tid;
			pthread_create(&tid,nullptr,Routine,(void*)&sock);
			
		}
	}
	return 0;
}
