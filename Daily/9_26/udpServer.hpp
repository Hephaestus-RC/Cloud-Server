#pragma once
#include<iostream>
#include<string>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

using namespace std;

class Server
{
	private:
		socket_t sock;
		int port;
		string ip;
	public:
		Server(string _ip = "127.0.0.1",int _port = 8080)
			:port(_port)
			 ,ip(_ip)
			 ,sock(-1)
		{
			
		}
		void Init()
		{
			//make sock
			sock = socket(AF_INET,SOCK_DGRAM,0);
			if(sock<0)
			{
				cerr<<"socket Init error! sock :"<<sock<<endl;
				exit(2);
			}
			cout<<"sock success!"<<endl;

			//bind
			struct sockaddr_in s;
			s.sin_family = AF_INET;
			s.sin_port = htons(port);
			s,sin_addr.s_addr = inet_addr(ip.c_str());

			if(bind(sock,(struct sockadd*)&s,sizeof(s)) < 0)
			{
				cerr<<"bind error"<<endl;
				exit(3);
			}
			cout<<"Bind success!"<<endl;

		}
		void Start()
		{
			char buf[1024];
			for(;;)
			{
				struct sockaddr_in peer;
				socklen_t len = sizeof(perr);
				ssize_t s = recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&peer,&len);
				if(s>0)
				{
					buf[s] = 0;
					cout<<"get Client message :"<<buf<<endl;
					sendto(sock,buf,strlen(buf),0,(struct sockaddr*)&peer,len);
				}
			}
		}
		~Server()
		{

		}
};
