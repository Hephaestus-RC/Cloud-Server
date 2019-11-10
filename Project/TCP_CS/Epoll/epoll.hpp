#pragma once
#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<string>
#include<sys/epoll.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>

using namespace std;

class Server
{
	private:
		int port;
		int lsock;
		int epfd;
	public:
		Server(int _port = 8080):port(_port),lsock(-1),epfd(-1){}
		void InitServer()
		{
			//1.创建监听套接字
			lsock = socket(AF_INET,SOCK_STREAM,0);
			if(lsock < 0)
			{
				cerr<<"sokcet error!"<<endl;
				exit(2);
			}
			cout<<"socket success!"<<endl;

			//2.绑定套接字和端口号
			struct sockaddr_in local;
			local.sin_family = AF_INET;
			local.sin_port = htons(port);
			local.sin_addr.s_addr = htonl(INADDR_ANY);
			if(bind(lsock,(struct sockaddr*)&local,sizeof(local))<0)
			{
				cerr<<"bind error"<<endl;
				exit(3);
			}
			cout<<"bind success!"<<endl;

			//3.将服务器设置为监听状态
			if(listen(lsock,5)<0)
			{
				cerr<<"listen error!"<<endl;
				exit(4);
			}
			cout<<"listen success!"<<endl;

			//4.设置端口复用
			int opt = 1;
			setsockopt(lsock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
		}
		void HandEvents(int num,struct epoll_event* evs)
		{

			for(int i = 0;i<num;++i)
			{
				//分情况讨论：1.新连接到来
				//		      2.事件就绪
				//情况一：
				if(evs[i].data.fd == lsock)
				{
					struct sockaddr_in peer;
					socklen_t len = sizeof(peer);
					int sock = accept(lsock,(struct sockaddr*)&peer,&len);
					if(sock < 0)
					{
						cout<<"New-sock Get Error!"<<endl;
						continue;
					}
					cout<<"Get New Link!"<<endl;
					struct epoll_event ev;
					ev.events = EPOLLIN;
					ev.data.fd = sock;
					epoll_ctl(epfd,EPOLL_CTL_ADD,sock,&ev);
				}
				
				//情况二：
				else
				{
					//读事件就绪
					if(evs[i].events & EPOLLIN)
					{
						char buf[1024];
						int sock = evs[i].data.fd;
						ssize_t s = recv(sock,buf,sizeof(buf)-1,0);
						if(s > 0)
						{
							buf[s] = 0;
							cout<<buf<<endl;
							//将接受内容打印之后，在将关注事件设置为写事件
							struct epoll_event ev;
							ev.data.fd = sock;
							ev.events = EPOLLOUT;
							epoll_ctl(epfd,EPOLL_CTL_MOD,sock,&ev);
						}
						else if(s == 0)
						{
							cout<<"Link Quit..."<<endl;
							close(sock);
							epoll_ctl(epfd,EPOLL_CTL_DEL,sock,nullptr);
						}
						else
						{
							cout<<"recv error!"<<endl;
							close(sock);
							epoll_ctl(epfd,EPOLL_CTL_DEL,sock,nullptr);
						}
					}//读
					
					//写事件就绪
					if(evs[i].events & EPOLLOUT)
					{
						int sock = evs[i].data.fd;
						//string s="HTTP/1.1 200 OK\r\n\r\n<html><body><h1>Hello RC</h1></body></html>";
						string s = "HTTP/1.1 200 OK\r\n\r\n<html><body><h1>Hello RC</h1></body></html>";
						send(sock,s.c_str(),s.size(),0);
						epoll_ctl(epfd,EPOLL_CTL_DEL,sock,nullptr);
						close(sock);
					}//写
			
				}//情况二
			}
		}
		void Run()
		{
			//创建出epoll模型
			epfd = epoll_create(256);
			if(epfd < 0)
			{
				cerr<<"epoll_create error!"<<endl;
				exit(5);
			}
			//将需要关注的事件和文件描述符设置进epoll模型中
			struct epoll_event ev;
			ev.events = EPOLLIN;
			ev.data.fd = lsock;
			epoll_ctl(epfd,EPOLL_CTL_ADD,lsock,&ev);
			
			//这个数组用于接收接收已经就绪的事件
			struct epoll_event evs[128];

			for(;;)
			{
				int num = epoll_wait(epfd,evs,128,-1);
				switch(num)
				{
					case 0:
						cout<<"Time out..."<<endl;
						break;
					case -1:
						cout<<"Epoll wait error!"<<endl;
						break;
					default:
						HandEvents(num,evs);
						break;
				}
			}
		}
		~Server()
		{
			if(lsock >= 0)
				close(lsock);
			if(epfd >= 0)
				close(epfd);
		}
};
