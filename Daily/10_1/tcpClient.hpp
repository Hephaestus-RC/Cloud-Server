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

class TcpClient
{
	private:
		int sock;
		int port;
		string ip;
	public:
		TcpClient(string _ip,int _port)
			:ip(_ip)
			,port(_port)
		{
			sock = -1;
		}
		void InitClient()
		{
			//sock
			sock = socket(AF_INET,SOCK_STREAM,0);
			if(sock < 0)
			{
				cerr<<"sock error"<<endl;
				exit(2);
			}
			cout<<"sock success! sock : "<<sock<<endl;
			
		}
		void Run()
		{
			struct sockaddr_in peer;
			peer.sin_family = AF_INET;
			peer.sin_addr.s_addr = inet_addr(ip.c_str());
			peer.sin_port = htons(port);
			socklen_t len = sizeof(peer);
			
			//connect
			int s = connect(sock,(struct sockaddr*)&peer,len);
			if(s<0)
			{
				cerr<<"Client connect error!"<<endl;
				exit(3);
			}
			cout<<"Client connect success!"<,endl;
		}
		~TcpServer()
		{

		}
};
