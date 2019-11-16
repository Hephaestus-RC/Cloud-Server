#ifndef __HTTPSERVER_HPP__
#define __HTTPSERVER_HPP__

#include"Protocol.hpp"
#include"Util.hpp"

#define DEFAULT_PORT 8080
#define BACKLOG 10

class Sock
{
	private:
		int sock;
		int port;
 	public:
		Sock(int _port = DEFAULT_PORT):port(_port),sock(-1)
		{}
		void Socket()
		{
			sock = socket(AF_INET,SOCK_STREAM,0);
			if(sock < 0)
			{
				cerr<<"Socket Error!"<<endl;
				exit(2);
			}
			int opt = 1;
			setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
		}
		void Bind()
		{
			struct sockaddr_in local;
			local.sin_family = AF_INET;
			local.sin_addr.s_addr = htonl(INADDR_ANY);
			local.sin_port = htons(port);

			if(bind(sock,(struct sockaddr*)&local,sizeof(local))<0)
			{
				cerr<<"Bind Error!"<<endl;
				exit(3);
			}
		}
		void Listen()
		{
			if(listen(sock,BACKLOG)<0)
			{
				cerr<<"Listen Error!"<<endl;
				exit(4);
			}
		}
		int Accept()
		{
			struct sockaddr_in peer;
			socklen_t len = sizeof(peer);
			int n_sock = accept(sock,(struct sockaddr*)&peer,&len);
			if(n_sock<0)
			{
				cerr<<"Accept Error!"<<endl;
				return -1;
			}
			cout<<"Get A New Link...Done!"<<endl;
			return n_sock;
		}
		~Sock()
		{
			if(sock >= 0)
				close(sock);
		}
};

class HttpServer
{
	private:
		Sock sock;
	public:
		HttpServer(int _port = DEFAULT_PORT):sock(_port)
		{}
		void InitHttpServer()
		{
			sock.Socket();
			sock.Bind();
			sock.Listen();
		}
		void Start()
		{
			int n_sock;
			for(;;)
			{
				n_sock = sock.Accept();
				if(n_sock >= 0)
				{
					int* so = new int(n_sock);
					pthread_t tid;
					pthread_create(&tid,nullptr,Entry::HandlRequest,(void*)so);
				}
			}
		}
		~HttpServer()
		{}
};







#endif
