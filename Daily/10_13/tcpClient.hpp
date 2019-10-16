#pragma once

#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<string>
#include<cstring>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>

using namespace std ;

class Client
{
	private:
		int sock;
		string ip;
		int port;
	public:
		Client(string _ip,int _port)
			:ip(_ip)
			,port(_port)
		{
			sock = -1;
		}
		void InitClient()
		{
			sock = socket(AF_INET,SOCK_STREAM,0);
			if(sock < 0)
			{
				cerr<<"socket error"<<endl;
				exit(2);
			}
			cout<<"sock success!"<<endl;

		}
		void Run()
		{
			struct sockaddr_in peer;
			peer.sin_family = AF_INET;
			peer.sin_addr.s_addr = inet_addr(ip.c_str());
			peer.sin_port = htons(port);
			if(connect(sock,(struct sockaddr*)&peer,sizeof(peer)) < 0)
			{
				cerr<<"connect  error"<<endl;
				exit(2);
			}
			else
			{
				cout<<"connect success!"<<endl;
				string s;
				string s1 = "quit";
				char buf[1024];
				for(;;)
				{
					cout<<"Please Enter #";
					cin>>s;
					if(s == s1)
					{
						send(sock,s.c_str(),0,0);
						break;
					}
					else
						send(sock,s.c_str(),s.size(),0);
					ssize_t s = recv(sock,buf,sizeof(buf)-1,0);
					if(s > 0)
					{
						buf[s] = 0;
						cout<<"echo#"<<buf<<endl;
					}
				}
			}
		}
		~Client()
		{
			if(sock > 0)
			{
				close(sock);
			}
		}	
};
