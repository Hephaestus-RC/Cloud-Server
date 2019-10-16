#pragma once

#include<iostream>
#include<string>
#include<cstring>
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>

class TcpServer
{
	private:
		int sock;
		int port;
		string ip;
	public:
		TcpServer(string _ip,int _port)
			:ip(_ip)
			,port(_port)
		{
			sock = -1;
		}
		void InitServer()
		{
			//sock
			sock = socket(AF_INET,SOCK_STREAM,0);
			if(sock < 0)
			{
				cerr<<"sock error"<<endl;
				exit(2);
			}
			cout<<"sock success! sock : "<<sock<<endl;
			
			//bind
			struct sockaddr_in peer;
			peer.sin_family = AF_INET;
			peer.sin_addr.s_addr = inet_addr(ip.c_str());
			peer.sin_port = htons(port);
			if(bind(sock,(struct sockaddr*)&peer,sizeof(peer))<0)
			{
				cerr<<"bind error!"<<endl;
				exit(3);
			}
			cout<<"bind success!"<<endl;
			
			//listen
			int s = listen(sock,5);
			if(s < 0)
			{
				cout<<"Server Listen Error"<<endl;
				exit(4);
			}
			cout<<"Server Listen Success!"<<endl;
		}
		void ServerIO(int sock)
		{

		}
		void Start()
		{
			struct sockaddr_in peer;
			peer.sin_family = AF_INET;
			peer.sin_addr.s_addr = inet_addr(ip.c_str());
			peer.sin_port = htons(port);
			socklen_t len = sizeof(peer);
			int c_sock = accept(sock,(struct sockaddr*)&peer,&len,0);
			ServerIO(c_sock);

		}
		~TcpServer()
		{

		}
};
