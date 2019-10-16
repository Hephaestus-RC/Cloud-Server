#pragma once

#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<string>
#include<cstring>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<pthread.h>
#include"ThreadPool.hpp"

using namespace std ;

class Server
{
	private:
		int l_sock;
		string ip;
		int port;
		ThreadPool* tp;
	public:
		Server( int _port=8080)
			:port(_port)
			,tp(nullptr)
		{
			l_sock = -1;
		}
		void InitServer()
		{
			l_sock = socket(AF_INET,SOCK_STREAM,0);
			if(l_sock < 0)
			{
				cerr<<"socket error"<<endl;
				exit(2);
			}
			cout<<"sock success!"<<endl;

			struct sockaddr_in local;
			bzero((void*)&local,sizeof(local));
			local.sin_family = AF_INET;
			local.sin_addr.s_addr = htonl(INADDR_ANY);
			local.sin_port = htons(port);
			if(bind(l_sock,(struct sockaddr*)&local,sizeof(local)) < 0)
			{
				cerr<<"bind error"<<endl;
				exit(3);
			}
			cout<<"bind success!"<<endl;

			if(listen(l_sock,5) < 0)
			{
				cerr<<"listen error"<<endl;
				exit(4);
			}
			cout<<"listen success"<<endl;
			cout<<"PID:"<<getpid()<<endl;
			
			tp = new ThreadPool();
			tp->InitPool();
		}
//		static void ServerIO(int sock)
//		{
//			for(;;)
//			{
//				char buf[1024];
//				int s = recv(sock,buf,sizeof(buf),0);
//				if(s > 0)
//				{
//					buf[s]= 0;
//					cout<<"Get Client #"<<buf<<endl;
//					send(sock,buf,s,0);
//				}
//				else if(s == 0)
//				{
//					cout<<"Client quit..."<<endl;
//					break;
//				}
//			}
//		}
//		static void* Routine(void* s)
//		{
//			pthread_detach(pthread_self());
//			int sock = *(int*)s;
//			ServerIO(sock);
//			close(sock);
//		}
		void Start()
		{
			struct sockaddr_in peer;
			socklen_t len = sizeof(peer);
			for(;;)
			{
				int sock = accept(l_sock,(struct sockaddr*)&peer,&len);
				if(sock > 0)
				{
					cout<<"Get New Link :"<<inet_ntoa(peer.sin_addr)<<" : "<<ntohs(peer.sin_port)<<endl;
					
					//thread-pool
					Task t(sock);
					tp->PushTask(t);
					
					//multi-thread	
					//pthread_t tid;
					//pthread_create(&tid,nullptr,Routine,(void*)&sock);
				}else
				{
					cerr<<"accept error"<<endl;
				}
			}
		}
		~Server()
		{
			if(l_sock > 0)
			{
				close(l_sock);
			}
			if(tp)
				delete tp;
		}	
};
