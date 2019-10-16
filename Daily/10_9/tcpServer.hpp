#pragma once
#include<iostream>
#include<string>
#include<strings.h>
#include<cstring>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

using namespace std;

class Server
{
	private:
		int listen_sock;
		int port;
		string ip;
	public:
		Server(string _ip="127.0.0.1",int _port = 8080)
			:ip(_ip)
			,port(_port)
			,listen_sock(-1)
		{}
		void InitServer()
		{
			//socket
			listen_sock = socket(AF_INET,SOCK_STREAM,0);
			if(listen_sock < 0)
			{
				cerr<<"socket error"<<endl;
				exit(2);
			}
			cout<<"listen_socket success!"<<endl;

			//bind
			struct sockaddr_in local;
			bzero((void*)&local,sizeof(local));
			local.sin_family = AF_INET;
			local.sin_addr.s_addr = inet_addr(ip.c_str());
			local.sin_port = htons(port);
			if(bind(listen_sock,(struct sockaddr*)&local,sizeof(local))<0)
			{
				cerr<<"bind error"<<endl;
				exit(3);
			}
			cout<<"bind success!"<<endl;

			//listen
			if(listen(listen_sock,5)<0)
			{
				cerr<<"listen error"<<endl;
				exit(4);
			}
			cout<<"listen success!"<<endl;

		}
		void ServerIO(int sock)
		{
			char buf[1024];
			for(;;)
			{
				int s = read(sock,buf,sizeof(buf));
				if(s == 0)
				{
					cout<<"client quit..."<<endl;
					break;
				}
				else if (s > 0)
				{
					buf[s] = 0;
					cout<<"Get Client# "<<buf<<endl;
					write(sock,buf,s);
				}
				else
				{
					break;
				}
			}
		}
		void Start()
		{	
			for(;;)
			{
				struct sockaddr_in peer;
				bzero((void*)&peer,sizeof(peer));
				socklen_t len = sizeof(peer);
				int sock = accept(listen_sock,(struct sockaddr*)&peer,&len);
				if(sock < 0)
				{
					cout<<"listen error"<<endl;
				}

				ServerIO(sock);
				close(sock);
			}
		}
		~Server()
		{
			if(listen_sock > 0)
				close(listen_sock);
		}
};
