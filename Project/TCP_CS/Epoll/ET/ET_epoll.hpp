#pragma once

#include<iostream>
#include<sys/types.h>
#include<sys/epoll.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdlib.h>
#include<fcntl.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string>

using namespace std;

//将文件描述符设置为非阻塞状态
void SetNonBlock(int fd)
{
	int fl = fcntl(fd,F_GETFL);
	fcntl(fd,F_SETFL,fl|O_NONBLOCK);
}
class Server
{
	private:
		int lsock;
		int port;
		int epfd;
	public:
		Server(int port_ = 8080)
			:port(port_)
			,lsock(-1)
			,epfd(-1)
		{}
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

			//5.创建epoll模型
			if((epfd = epoll_create(256)) < 0)
			{
				cerr<<"epoll_create error!"<<endl;
				exit(5);
			}

			//将监听套接字设置为非阻塞状态
			SetNonBlock(lsock);
		}
		//因为是ET模式，所以必须将新连接一次性接收完
		void Accept(int sock)
		{
			struct sockaddr_in peer;
			struct epoll_event ev;
			for(;;)
			{
				socklen_t len = sizeof(peer);
				int new_sock = accept(lsock,(struct sockaddr*)&peer,&len);
				if(sock < 0)
					break;
				cout<<"Get New Link"<<endl;
				SetNonBlock(new_sock);
				ev.data.fd = new_sock;
				ev.events = EPOLLIN | EPOLLET;
				epoll_ctl(epfd,EPOLL_CTL_ADD,new_sock,&ev);
			}
		}
		//因为是ET模式，所以必须一次性将数据接受完
		ssize_t Recv(char* buf,int sock)
		{
			ssize_t total = 0;
			ssize_t num = 0;
			while((num = recv(sock,buf+total,64,0)) > 0)
			{
				total+=num;
			}
			if(num == 0)
			{
				cout<<"Link Quit..."<<endl;
				epoll_ctl(epfd,EPOLL_CTL_DEL,sock,nullptr);
				close(sock);

			}
			else 
			{
				cout<<"Recv Error!"<<endl;
				epoll_ctl(epfd,EPOLL_CTL_DEL,sock,nullptr);
				close(sock);
			}
			return total;
		}
		//事件就绪后先读再写
		void HandEvents(int num,struct epoll_event* evs)
		{
			struct epoll_event ev;
			//发送缓冲区
			string s_buf="HTTP/1.1 200 OK\r\n\r\n<html><body><h1>Hello .This is RC EPOLL-Sever</h1></body></html>";
			int sock;
			for(int i = 0; i < num; ++i)
			{
				//判断是新连接到来还是事件就绪
				if(evs[i].data.fd == lsock)
				{
					Accept(evs[i].data.fd);
				}
				//事件就绪
				else
				{
					char buf[1024];
					sock = evs[i].data.fd;
					//读事件
					if(evs[i].events & EPOLLIN)
					{
						Recv(buf,sock);
					}//读
					//写事件
					else if(evs[i].events & EPOLLOUT)
					{
						send(sock,s_buf.c_str(),s_buf.size(),0);
						close(sock);
						epoll_ctl(epfd,EPOLL_CTL_DEL,sock,nullptr);
					}//写
					else
					{
						cout<<"Error Things Ready!"<<endl;
						epoll_ctl(epfd,EPOLL_CTL_DEL,sock,nullptr);
						close(sock);
					}
				}
			}//for
		}
		void Run()
		{
			//设置监听套接字事件（接收连接事件）
			struct epoll_event ev;
			ev.events = EPOLLIN | EPOLLET;
			ev.data.fd = lsock;
			
			//首先将监听套接字lsock设置进epoll模型中
			epoll_ctl(epfd,EPOLL_CTL_ADD,lsock,&ev);

			struct epoll_event evs[128];
			for(;;)
			{
				int timeout = -1;
				int num = epoll_wait(epfd,evs,128,timeout);
				switch(num)
				{
					case 0:
						cout<<"Time out..."<<endl;
						break;
					case -1:
						cout<<"Epoll Wait Error!"<<endl;
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
