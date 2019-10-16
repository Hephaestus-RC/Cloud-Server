#pragma once
#include<iostream>
#include<string>
#include<strings.h>
#include<cstring>
#include<unistd.h>
#include<stdlib.h>
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
		Client(string _ip="127.0.0.1",int _port = 8080)
			:ip(_ip)
			,port(_port)
			,sock(-1)
		{}
		void InitClient()
		{
			//socket
			sock = socket(AF_INET,SOCK_STREAM,0);
			if(sock < 0)
			{
				cerr<<"socket error"<<endl;
				exit(2);
			}
			cout<<"socket success!"<<endl;
		}
		void Run()
		{	
			struct sockaddr_in peer;
			bzero((void*)&peer,sizeof(peer));
			peer.sin_family = AF_INET;
			peer.sin_addr.s_addr = inet_addr(ip.c_str());
			peer.sin_port = htons(port);
			if(connect(sock,(struct sockaddr*)&peer,sizeof(peer))<0)
			{
				cerr<<"connect error"<<endl;
				exit(2);
			}
			cout<<"connect success!"<<endl;
			string msg;
			char buf[1024];
			string s("quit");
			for(;;)
			{
				cout<<"Please Enter# ";
				cin>>msg;
				write(sock,msg.c_str(),msg.size());
				if(msg == s)
					break;
			}
			close(sock);
		}
		~Client()
		{
			if(sock > 0)
				close(sock);
		}
};
