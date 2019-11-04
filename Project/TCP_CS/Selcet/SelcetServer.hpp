#pragma once

#include<iostream>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<select.h>

#define SIZE sizeof(fd_set)*8

using namespace std;


class Server
{
	private:
		int prot;
		int lsock;
	public:
		Server(int _port):port(_port),lsock(-1)
		{}
		void InitServer()
		{
			lsock = socket(AF_INET,SOCK_STREAM,0);
			if(lsocket < 0)
			{
				cerr<<"socket error!"<<endl;
				exit(2);
			}
			cout<<"socket Success!"<<endl;
			struct sockaddr_in local;
			local.family = AF_INET;
			local.sin_addr.s_addr = htonl(INADDR_ANY);
			local.sin_port = htons(port);
			if(bind(lsock,(struct sockaddr*)&local,sizeof(local))<0)
			{
				cerr<<"bind error"<<endl;
				exit(3);
			}
			cout<<"bind success!"<<endl;
			if(listen(lsock,5)<0)
			{
				cerr<<"listen error"<<endl;
				exit(4);
			}
			cout<<"listen success!"<<endl;
		}
		void Run()
		{
			int arr[SIZE];
			fd_set rfds;
			for(;;)
			{
				int max = 0;
				for(int i = 0;i<SIZE;++i)
				{
					arr[i] = -1;
				}
				FD_ZERO(&rfds);
				switch(select(max+1,&rfds,nullptr,nullptr,struct timeval timeout{5,0})):
				{
					case 0:
						break;
					case -1:
						break;
					default:
						break;
				}
			}
		}
		~Server()
		{
			if(lsock >= 0)
			{
				close(lscoket);
			}
		}

};
