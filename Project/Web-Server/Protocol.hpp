#ifndef __PROTOCOL_HPP__
#define __PROTOCOL_HPP__

#include<iostream>
#include<unistd.h>
#include<stdlib.h>
#include<string>
#include<sstream>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<pthread.h>

using namespace std;

class HttpRequest
{
	private:
		string request_line;
		string request_header;
		string request_blank;
		string request_body;
	private:
		string method;
		string uri;
		string version;
	public:
		HttpRequest()
		{}
		string& GetRequestLine()	//设置请求行
		{
			return request_line;
		}
		string& GetRequestHeader()	//设置请求报头
		{
			return request_header;
		}
		string& GetRequestBlank()	//设置空行
		{
			return  request_blank;
		}
		string& GetRequestBody()	//设置请求正文
		{
			return request_body;
		}		
		bool MethodIsLegal()
		{

		}
		void RequestLineParse()		//解析请求行
		{
			stringstream ss(request_line);
			ss>>method>>uri>>version;//自动分离
		}
		//解析请求报头
		//解析请求正文
		~HttpRequest()
		{}
};
class HttpResponse
{
	private:
		string response_line;
		string response_head;
		string response_blank;
		string response_body;
	public:
		HttpResponse()
		{}
		~HttpResponse()
		{}
};


//读请求  发响应
class EndPoint
{
	private:
		int sock;
	public:
		EndPoint(int _sock):sock(_sock)
		{}
		//读一行
		int RecvLine(string& line) //将所有不同格式的行分隔符都转换成'\n'
		{
			char c = 'X';
			while(c!='\n')
			{
				ssize_t s = recv(sock,c,1,0); // \n  \r  \r\n
				if(s > 0)
				{
					if(c=='\r') //行分隔符有可能是\r or \r\n
					{
						if(recv(sock,c,1,MSG_PEEK) > 0)//MSG_PEEK相当于探针，可以探测出下一个内容
						{
							if(c=='\n') //确定行分隔符是\r\n
								recv(sock,c,1,0);
							else		//确定行分隔符是\r
								c = '\n'；
						}
						else
							c = '\n'; //防止因缓冲区无数据recv，而导致c中保存随机值；
					}//(c=='\r')
					line.push_back(c);
				}
				else
				{//(s<0)
					c='\n';
					line.push_back(c);
				}
			}
			return line.size();
		}
		void RecvRequestLine(HttpRequest* rq)
		{
			RecvLine(rq->GetRequestLine());		//接收请求行
			RecvHeader(rq->GetRequestHeader()); //接收请求报头
			RecvBlank(rq->GetRequestBlank());	//接收空行
			RecvBody(rq->GetRequestBody());		//接收请求正文
		}
		~EndPoint()
		{}
};

class Entry
{
	public:
		static void* HandlRequest(void* args)
		{
			int sock = *(int*)args;
			EndPoint* ep = new EndPoint(sock);
			HttpRequest* rq = new HttpRequest();
			HttpResponse* rsp = new HttpResponse();
			
			ep->RecvRequestLine(rq);	//?	接收请求报文
			rq->RequestLineParse();		//解析请求行
			
			if(MethodIsLegal())		//判定请求方法是否合法
			{//........
			}
			
			
			
			
			delete args;
			delete ep;
			delete rq;
			delete rsp;
		}
};







#endif
