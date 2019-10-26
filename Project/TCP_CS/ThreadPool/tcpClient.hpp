#pragma once

#include"headfile.h"

class Client
{
	private:
		int port;
		int sock;
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
			sock = socket(AF_INET,SOCK_STREAM,0);
			if(sock<0)
			{
				cerr<<"sock error"<<endl;
				exit(2);
			}
			cout<<"sock success!"<<endl;
		}
		void Run()
		{
			struct sockaddr_in peer;
			peer.sin_family = AF_INET;
			peer.sin_port = htons(port);
			peer.sin_addr.s_addr = inet_addr(ip.c_str());
			if(connect(sock,(struct sockaddr*)&peer,sizeof(peer))<0)
			{
				cerr<<"connect error"<<endl;
				exit(3);
			}
			string key;
			for(;;)
			{
				char buf[1024];
				cout<<"Enter The World: ";
				cin>>key;
				send(sock,key.c_str(),key.size(),0);
				int s = recv(sock,buf,sizeof(buf)-1,0);
				if(s > 0)
				{
					buf[s] = 0;
					cout<<"Echo :"<<buf<<endl;
				}
				else
					break;
			}
		}
		~Client()
		{
			close(sock);
		}
};
