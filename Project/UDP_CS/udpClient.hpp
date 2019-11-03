#pragma once

#include<iostream>
#include<string>
#include<cstring>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

using namespace std;

class Client
{
	private:
		int sock;
		int peer_port;
		string peer_ip;
	public:
		Client(string _ip="127.0.0.1",int _port = 8080)
			:peer_ip(_ip)
			,peer_port(_port)
		{
			sock = -1;
		}
		void InitClient()
		{
			sock = socket(AF_INET,SOCK_DGRAM,0);
			if(sock<0)
			{
				cerr<<"socket error!"<<endl;
				exit(2);
			}
			cout<<"Client socket success!  "<<endl;
		}
		void Run()
		{
			string message;
			char buf[1024];
			for(;;)
			{
				cout<<"Please Enter #";
				cin>>message;
				if(message.c_str() == "exit")
					return ;
				struct sockaddr_in server;
				server.sin_family = AF_INET;
				server.sin_addr.s_addr = inet_addr(peer_ip.c_str());
				server.sin_port = htons(peer_port);

				socklen_t len = sizeof(server);
				
				//client to server
				sendto(sock,message.c_str(),message.size(),0,(struct sockaddr*)&server,len);
				
				//server back-to client
				ssize_t s = recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&server,&len);
				if(s > 0)
				{
					buf[s] = 0;
					cout<<"return back:"<<buf<<endl;
				}
			}
		}
		~Client()
		{

		}

};
