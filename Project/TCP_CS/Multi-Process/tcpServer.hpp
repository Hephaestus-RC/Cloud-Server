#pragma once
#include<iostream>
#include<string>
#include<strings.h>
#include<cstring>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>



using namespace std;

class Server
{
	private:
		int listen_sock;
		int port;
		string ip;
	public:
		Server(string _ip="127.0.0.1",int _port = 8080)
			:ip(_ip)
			,port(_port)
			,listen_sock(-1)
		{}
		void InitServer()
		{
			//socket
			listen_sock = socket(AF_INET,SOCK_STREAM,0);
			if(listen_sock < 0)
			{
				cerr<<"socket error"<<endl;
				exit(2);
			}
			cout<<"listen_socket success!"<<endl;

			//bind
			struct sockaddr_in local;
			bzero((void*)&local,sizeof(local));
			local.sin_family = AF_INET;
			local.sin_addr.s_addr = inet_addr(ip.c_str());
			local.sin_port = htons(port);
			if(bind(listen_sock,(struct sockaddr*)&local,sizeof(local))<0)
			{
				cerr<<"bind error"<<endl;
				exit(3);
			}
			cout<<"bind success!"<<endl;

			//listen
			if(listen(listen_sock,5)<0)
			{
				cerr<<"listen error"<<endl;
				exit(4);
			}
			cout<<"listen success!"<<endl;
			cout<<"PID:"<<getpid()<<endl;

		}
		void ServerIO(int sock)
		{
			char buf[1024];
			for(;;)
			{
				int s = read(sock,buf,sizeof(buf));
				if(s == 0)
				{
					break;
				}
				else if (s > 0)
				{
					buf[s] = 0;
					cout<<"Get Client("<<sock<<")# "<<buf<<endl;
					write(sock,buf,s);
				}
				else
				{
					break;
				}
			}
		}

		void Start()
		{
			//signal-function can let father don't wait child , father ignore child's signal
			//so child isn't Zombei
			signal(SIGCHLD,SIG_IGN);
			
			for(;;)
			{
				struct sockaddr_in peer;
				bzero((void*)&peer,sizeof(peer));
				socklen_t len = sizeof(peer);
				int sock = accept(listen_sock,(struct sockaddr*)&peer,&len);
				if(sock < 0)
				{
					cout<<"accept error"<<endl;
					continue;
				}
				cout<<"	Get A New Client[IP : PORT]:"<< inet_ntoa(peer.sin_addr) << ":" << ntohs(peer.sin_port) <<endl;
				pid_t id = fork();
				if(id == 0)
				{//child
					close(listen_sock);
					ServerIO(sock);
					close(sock);
					cout<<"Client[IP : PORT] quit..."<< inet_ntoa(peer.sin_addr) << ":" << ntohs(peer.sin_port) <<endl;
					exit(0);//very important: child should exit when child-process finish ServerIO
				}
				else
				{//father
					close(sock);
				}
			}
		}
		~Server()
		{
			if(listen_sock > 0)
				close(listen_sock);
		}
};
