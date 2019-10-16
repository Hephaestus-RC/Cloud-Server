#pragma once

#include<iostream>
#include<string>
#include<cstring>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

using namespace std;

class Client
{
	private:
		int sock;
		int port;
		string ip;
	public:
		Client(string _ip ,int _port)
			:ip(_ip)
			,port(_port)
		{
			sock = -1;
		}
		void InitClient()
		{
			sock = socket(AF_INET,SOCK_DGRAM,0);
			if(sock < 0)
			{
				cerr<<"sock errror"<<endl;
				exit(2);
			}
			cout<<"sock success!"<<endl;
		}
		void Run()
		{
			string msg;
			char buf[1024];
			for(;;)
			{
				cout<<"Client# ";
				//cin>>msg;
				getline(cin,msg);
				struct sockaddr_in peer;
				peer.sin_family = AF_INET;
				peer.sin_addr.s_addr = inet_addr(ip.c_str());
				peer.sin_port = htons(port);
				socklen_t len = sizeof(peer);

				sendto(sock,msg.c_str(),msg.size(),0,(struct sockaddr*)&peer,len);
				
				int s = recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&peer,&len);
				if(s > 0)
				{
					buf[s] = 0;
					cout<<"Server call-back :"<<buf<<endl;
				}
				else
					cout<<"recvfrom error!"<<endl;
			}
		}
		~Client()
		{

		}
};
