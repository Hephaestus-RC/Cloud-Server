#pragma once

#include<iostream>
#include<string>
#include<cstring>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

using namespace std;

class Server
{
	private:
		int sock;
		string ip;
		int port;
	public:
		Server(string _ip = "127.0.0.1",int _port = 8080)
			:ip(_ip)
			,port(_port)
		{
			sock = -1;
		}
		void InitServer()
		{
			//socket    AF_INET:IPv4    SOCK_DGRAM:UDP
			sock = socket(AF_INET,SOCK_DGRAM,0);
			if(sock<0)
			{
				cerr<<"socket error!"<<endl;
				exit(2);
			}
			cout<<"Server socket success! "<<endl;

			//bind
			struct sockaddr_in local;
			local.sin_family = AF_INET;
			local.sin_port = htons(port);
			local.sin_addr.s_addr = inet_addr(ip.c_str());
			
			if(bind(sock,(struct sockaddr*)&local,sizeof(local)) < 0)
			{
				cerr<<"bind error!"<<endl;
				exit(3);
			}
			cout<<"bind success"<<endl;
		}
		void Start()
		{
			char buf[1024];
			for(;;)
			{
				struct sockaddr_in peer;
				socklen_t len = sizeof(peer);
				int s = recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&peer,&len);
				if(s > 0)
				{
					buf[s] = 0;
					cerr<<"get client message : "<<buf<<endl;
					sendto(sock,buf,strlen(buf),0,(struct sockaddr*)&peer,len);
				}
			}
		}
		~Server()
		{
		}
};
