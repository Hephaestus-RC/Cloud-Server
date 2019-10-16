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

class Client
{
	private:
		int sock;
		int port;
		string ip;
	public:
		Client(string _ip,int _port)
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
				cerr<<"sock error"<<endl;
				exit(2);
			}
			cout<<"sock success!"<<endl;

		}
		void Run()
		{
			char buf[1024];
			string s;
			for(;;)
			{
				cout<<"Client# ";
				cin>>s;
				struct sockaddr_in peer;
				peer.sin_family = AF_INET;
				peer.sin_addr.s_addr = inet_addr(ip.c_str());
				peer.sin_port = htons(port);
				socklen_t len = sizeof(peer);
				sendto(sock,(void*)s.c_str(),s.size(),0,(struct sockaddr*)&peer,len);
				ssize_t size = recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&peer,&len);
				if(size < 0)
					cout<<"get nothing"<<endl;
				else
				{
					buf[size] = 0; 
					cout<<"client :"<<buf<<endl;
				}
			}
		}
		~Client()
		{

		}
};
