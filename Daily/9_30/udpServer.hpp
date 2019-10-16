#pragma once
#include<iostream>
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
		int port;
		int sock;
		string ip;
	public:
		Server(string _ip = "127.0.0.1",int _port = 8080)
			:ip(_ip)
			,port(_port)
		{
			sock = -1;
		}
		void InitServer()
		{
			sock = socket(AF_INET,SOCK_DGRAM,0);
			if(sock<0)
			{
				cerr<<"sock error"<<endl;
				exit(2);
			}
			cout<<"sock success !"<<endl;
			
			//bind
			struct sockaddr_in local;
			local.sin_family = AF_INET;
			local.sin_addr.s_addr = inet_addr(ip.c_str());
			local.sin_port = htons(port);
			if(bind(sock,(struct sockaddr*)&local,sizeof(local))<0)
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
				  int s = recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&peer,&len);
				if(s > 0)
				{
					buf[s] = 0;
					cout<<"Get Client->"<<buf<<endl;
					string msg;
					cin>>msg;
					sendto(sock,msg.c_str(),msg.size(),0,(struct sockaddr*)&peer,len);
				}
			}
		}
		~Server()
		{

		}
};
