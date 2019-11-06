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
			//1.创建监听套接字描述符
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
			
			//2.绑定端口和监听套接字
			if(bind(lsock,(struct sockaddr*)&local,sizeof(local))<0)
			{
				cerr<<"bind error"<<endl;
				exit(3);
			}
			cout<<"bind success!"<<endl;
			
			//3.将服务器设置为监听状态
			if(listen(lsock,5)<0)
			{
				cerr<<"listen error"<<endl;
				exit(4);
			}
			cout<<"listen success!"<<endl;

			//添加选项 --setsockopt  这样设置在关闭后再次绑定不会出错(解决地址复用问题)
			int opt = 1;
			setsockopt(lsock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
		}


		void Run()
		{
			int arr[SIZE];
			//vector<int> arr(SIZE);	//这个数组中的元素表示用户关心的文件描述符值(sock)
			for(int i = 0;i<SIZE;++i) //初始化这个数组
				arr[i] = -1;
			
			fd_set rfds;//定义读文件描述符集
			
			//将监听套接字放进数组的第一个位置
			arr[0] = lsock;
			
			int max = lsock;
			//开始处理连接请求和读写请求
			for(;;)
			{
				for(int i = 0;i<SIZE;++i) // 找出最大的文件描述符
					if(arr[i] > max)
						max = arr[i];

				//设置超时时间
				struct timeval timeout{5,0};
				FD_ZERO(&rfds);
			
				//将用户需要内核关注的套接字描述符设置进fds(读描述符集)
				for(int i = 0; i < SIZE; ++i)
				{
					if(arr[i]==-1)
						continue;
					FD_SET(arr[i],&rfds);
				}
				
				struct sockaddr_in peer;
				socklen_t len = sizeof(peer);

				int ret = select(max+1,&rfds,nullptr,nullptr,&timeout);
				//select返回时，有两种情况：1.服务器获取到了新连接；（连接建立事件和读事件相似）
				//                          2.某些连接上的某些事件已经就绪；
				
				switch(ret)
				{
					case 0:
						cout<<"Time Out!"<<endl;
						break;
					case -1:
						cerr<<"Select Error!"<<endl;
						return ;
						break;
					default:
						//1.listen_Socket获得连接
						if(FD_ISSET(arr[0]/*lsock*/,&rfds))
						{
							//select已经将等的工作完成，此时accept一定不会阻塞
							int sock = accept(lsock,(struct sockaddr*)&peer,&len);
							if(sock < 0)
							{
								cerr<<"accept error!"<<endl;
							}
							else
							{
								cout<<"Get A New Client!"<<endl;
								//将新连接的套接字描述符设置进数组
								int j = 1;
								for(j = 1; j < SIZE;++j)
								{
									if(arr[j] == -1)
									{
										arr[j] = sock;
										break;
									}
								}
								if(j == SIZE)
								{
									close(sock);
									cout<<"sock_array is full!"<<endl;
								}
							}
						}
						//2.已获得连接（普通链接）上有事件(读或写)就绪
						else
						{
							char buf[1024];
							for(int i = 1;i < SIZE;i++)
							{
								if(arr[i] == -1)
									continue;
								if(FD_ISSET(arr[i],&rfds))
								{
									//程序运行到这里，已经将读事件准备就绪,此时开始进行读操作，一定不会阻塞
									int s = recv(arr[i],buf,sizeof(buf)-1,0);

									if(s < 0)
									{
										cerr<<"recv error"<<endl;
										close(arr[i]);
										arr[i] = -1;
									}
									else if (s == 0)
									{
										cerr<<"Client end!"<<endl;
										close(arr[i]);
										arr[i] = -1;
									}
									else
									{
										buf[s] = 0;
										cout<<"Get # "<<buf<<endl;
									}
									//读操作完成后，将文件描述符关闭
									//close(arr[i]);
									//arr[i] = -1;
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
