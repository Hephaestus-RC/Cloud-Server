#pragma once

#include<iostream>
#include<sys/types.h>
#include<sys/socket.h>
#include<string>
#include<stdlib.h>
#include<arpa/inet.h>
#include<netinet/in.h>

using namespace std;

class Server
{
	private:
		int sock;
		int port;
		string ip;
	public:
		Server(int _port = 8080,string _ip = "127.0.0.1")
			:port(_port)
			,ip(_ip)
			,sock(-1)
		{
		}
		~Server()
		{

		}
		void InitServer()
		{
			//socket
			int sock = socket(AF_INET,SOCK_DGRAM,0);
			if(sock < 0)
			{
				cerr<<"socket error"<<endl;
				exit(2);
			}
			cout<<"Socket ... init success! sock:"<<sock<<endl;
			
			//bind
			struct socket_in local;						//socket
			local.sin_family = AF_INET;						//network type
			local.sin_port = htons(port);					//port
			local.sin_addr.s_addr = inet_addr(ip.c_str());	//ip

			if( bind(sock,(struct sockaddr*)&locak,sizeof(local)) < 0)
			{	
				cerr<<"bind error!"<<endl;
				exit(3);
			}
			cout<<"Bind success!"<<endl;
		}
		void Start()
		{
			//Server never don't stop
			char buf[1024];
			while(1)
			{
				struct sockaddr_in peer;
				socklen_t len = sizeof(peer);
				
				//get message
				ssize_t s = recvfrom(sock,(void*)buf,sizeof(buf)-1,0,(struct sockaddr*)&peer,&len);
				if( s > 0)
				{
					buf[s] = 0;
					cout<<" get Client message : "<<buf<<endl;
					//put message
					sendto(sock,buf,strlen(buf),0,(struct sockadd*)&peer,len);
				}


			}
		}
};
