#pragma once

#include<iostream>
#include<string>
#include<string.h>
#include<stdlib.h>
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
		Server(string _ip = "127.0.0.1",int _port = 8080)
			:ip(_ip)
		    ,port(_port)
		{
		}
		void InitServer()
		{
			//socket
			sock = socket(AF_INET,SOCK_DGRAM,0);
			if(sock < 0)
			{
				cerr<<"socket error!sock:"<<sock<<endl;
				exit(2);
			}
			cout<<"socket success!,sock : "<<sock<<endl;

			//bind
			struct sockaddr_in local;
			local.sin_family = AF_INET;
			local.sin_port = htons(port);
			local.sin_addr.s_addr = inet_addr(ip.c_str());
			if(bind(&sock,(struct sockaddr*)&local,sizeof(local))<0)
			{
				cerr<<"bind error!"<<endl;
				exit(3);
			}
			cout<<"bind  success!"<<endl;
		}
		void Start()
		{
			int buf[1024];
			for(;;)
			{
				struct sockaddr_in peer;
				socklen_t len = sizeof(peer);
				int size = recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&peer,&len);
				buf[size] = 0;
				cout<<"get client said : "<<buf<<endl;
				sendto(sock,buf,strlen(buf),0,(struct sockaddr*)&peer,size);
			}
		}
		~Server()
		{

		}
};
