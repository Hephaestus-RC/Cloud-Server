#pragma once

#include<iostream>
#include<unistd.h>
#include<stdlib.h>
#include<string>
#include<cstring>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

using namespace std;

class Server
{
	private:
		int sock;
		int port;
		string ip;
	public:
		Server(string _ip,int _port)
			:ip(_ip)
			,port(_port)
		{
			sock = -1;
		}
		void InitServer()
		{
			sock = socket(AF_INET,SOCK_DGRAM,0);
			if(sock < 0)
			{
				cerr<<"sock error"<<endl;
				exit(2);
			}
			cout<<"sock success!"<<endl;

			struct sockaddr_in peer;
			peer.sin_family = AF_INET;
			peer.sin_addr.s_addr = inet_addr(ip.c_str());
			peer.sin_port = htons(port);
			if(bind(sock,(struct sockaddr*)&peer,sizeof(peer))<0)
			{
				cerr<<"bind error"<<endl;
				exit(3);
			}
			cout<<"bind success!"<<endl;
		}
		void Start()
		{
			char buf[1024];
			for(;;)
			{
				struct sockaddr_in peer;
				socklen_t len = sizeof(peer);
				ssize_t s = recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&peer,&len);
				if(s > 0)
				{
					buf[s] = 0; 
					cout<<"client :"<<buf<<endl;
					sendto(sock,buf,strlen(buf),0,(struct sockaddr*)&peer,len);
				}
			}
		}
		~Server()
		{

		}
};
