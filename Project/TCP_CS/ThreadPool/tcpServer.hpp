#pragma once
#include"headfile.h"
#include"ThreadPool.hpp"

class Server
{
	private:
		int listen_sock;
		int port;
		ThreadPool* tp;
		//在这个Server中没有使用“127.0.0.1”这个地址
		//但是在client中必须使用本地回环地址，这样才可以连上Server
	public:
		Server(int _port = 8080)
			:port(_port)
		{
			listen_sock = -1;
		}
		void InitServer()
		{
			//1.socket;
			listen_sock = socket(AF_INET,SOCK_STREAM,0);
			if(listen_sock < 0)
			{
				cerr<<"sock error"<<endl;
				exit(2);
			}
			cout<<"sock success!"<<endl;

			//2.bind
			struct sockaddr_in local;
			local.sin_family = AF_INET;
			local.sin_port = htons(port);
			local.sin_addr.s_addr = htonl(INADDR_ANY);//任意接收一个链接到本机的IP(动态绑定任意IP)
			if(bind(listen_sock,(struct sockaddr*)&local,sizeof(local))<0)
			{
				cerr<<"bind error"<<endl;
				exit(3);
			}
			cout<<"bind success!"<<endl;

			//3.listen
			if(listen(listen_sock,5)<0)
			{
				cerr<<"listen error!"<<endl;
				exit(4);
			}
			cout<<"listen success!"<<endl;

			tp = new ThreadPool();
			tp->InitThreadPool();
		}
		void Start()
		{
			//4.accept
			struct sockaddr_in peer;
			socklen_t len = sizeof(peer);
			for(;;)
			{
				int sock = accept(listen_sock,(struct sockaddr*)&peer,&len);
				if(sock > 0)
				{
					cout<<"		Get New Link.."<<endl;
					Task t(sock);
					tp->PushTask(t);
				}
				else 
				{
					break;
				}
			//	close(sock);
			}
		}
		~Server()
		{
			if(listen_sock == -1)
			{
				close(listen_sock);
			}
			if(tp!=nullptr)
			{
				delete tp;
			}
		}
};


