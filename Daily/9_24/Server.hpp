#pragma once
#include<iostream>
#include<string>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>

class Server
{
	private:
		int port;
		string ip;
	public:
		Server(int _port,string _ip):port(_port),ip(_ip)
		{
		}
		void InitServer()
		{
			int socket = socket(AF_INET,SOCK_DGRAM,0);
			if(socket < 0)
			{
				cout<<"Socket Init failed !"<<endl;
				exit(2);
			} 
			bind(socket,);
		}
		void Start()
		{
			
		}
		~Server()
		{
			
		}
};
