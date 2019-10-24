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
			//将请求报文打印出来
			cout<<buf<<endl;
			cout<<"------------------------------------------------------------------"<<endl;
		
			
			//重定向版本的响应报文(临时重定向302，永久重定向301)
			//string response = {"HTTP/1.0 302 Found\r\nLocation: https://www.baidu.com\r\n\r\n"};
			//string response = {"HTTP/1.0 404 Not Found\r\n\r\n<html><body><center><h1>Page Not Found</h1></center></body></html>"};
			//string response = {"HTTP/1.0 504 Bad Gateway\r\n\r\n"};
			
			
			//添加cookie信息（set-cookie）
			//响应报文
			string response = {"HTTP/1.0 200 OK\r\nset-cookie: name=1864&pwd=159938\r\n\r\n<html><h1>OK!</h1></html>"};
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

	//端口复用：消除因为TIME_WAIT而导致的bind失败
	int opt = 1;
	setsockopt(listen_sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));


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
