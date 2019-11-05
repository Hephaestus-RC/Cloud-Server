#pragma once

#include<iostream>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/select.h>

#define SIZE sizeof(fd_set)*8

using namespace std;


class Server
{
	private:
		int port;
		int lsock;
	public:
		Server(int _port = 8080):port(_port),lsock(-1)
		{}
		void InitServer()
		{
			lsock = socket(AF_INET,SOCK_STREAM,0);
			if(lsock < 0)
			{
				cerr<<"socket error!"<<endl;
				exit(2);
			}
			cout<<"socket Success!"<<endl;
			struct sockaddr_in local;
			local.sin_family = AF_INET;
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

			//tianjia --setsockopt  it's not to bind error
			//-----------------------------------------------------------------------------
		}
		void Run()
		{
			int arr[SIZE];
			fd_set rfds;//duwenjianmiaoshufuji
			for(int i = 0;i<SIZE;++i)
			{
				arr[i] = -1;
			}
			for(;;)
			{
				int max = 0;
				for(int i = 0;i<SIZE;++i)
					if(arr[i] > max)
						max = arr[i];

				FD_ZERO(&rfds);
			
				//将监听套接字放进数组的第一个位置
				arr[0] = lsock;
				FD_SET(lsock,&rfds);//listen_sock set in rfds
				//将用户需要内核关注的套接字描述符设置进fds(读套接字集)
				for(int i = 0; i < SIZE; ++i)
				{
					if(arr[i]==1)
						continue;
					FD_SET(arr[i],&rfds);
				}
				

				struct timeval timeout{5,0};
				int ret = select(max+1,&rfds,nullptr,nullptr,&timeout);
				
				switch(ret)
				{
					case 0:
						cout<<"Time Out!"<<endl;
						break;
					case -1:
						cerr<<"Select Error!"<<endl;
						break;
					default:
						//listen_Socket获得连接
						if(FD_ISSET(arr[0],&rfds))
						{
							FD_SET(ret,&rfds);
							break;
						}
						//以获得连接上有事件就绪
						else
						{
							struct sockaddr_in peer;
							socklen_t len = sizeof(peer);
							char buf[1024];
							for(int i = 0;i < SIZE;i++)
							{
								if(FD_ISSET(arr[i],&rfds))
								{
									int sock = accept(lsock,(struct sockaddr*)&peer,&len);
									//changxuyunxingdaozheli yijing jiang dushijian zhunbeijiuxu
									int s = recv(sock,buf,sizeof(buf)-1,0);
									if(s < 0)
										cerr<<"recv error"<<endl;
									else if (s == 0)
										cerr<<"ercv end!"<<endl;
									else
									{
										buf[s] = 0;
										cout<<"Get # "<<buf<<endl;
									}
									close(arr[i]);
									arr[i] = -1;	
								}
							}
						}
						break;
				}
			}
		}
		~Server()
		{
			if(lsock >= 0)
			{
				close(lsock);
			}
		}

};
