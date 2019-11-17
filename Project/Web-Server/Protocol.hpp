#ifndef __PROTOCOL_HPP__
#define __PROTOCOL_HPP__

#include<iostream>
#include<unistd.h>
#include<stdlib.h>
#include<string>
#include<unordered_map>
#include<sstream>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<pthread.h>
#include"Util.hpp"

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
		unordered_map<string,string> um;
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
		string& GetRequestBody()	//设置请求正文
		{
			return request_body;
		}		
		bool MethodIsLegal()	//判断请求方法是否合法
		{
			if(method!="POST" && method!="GET")
				return false;
			return true;
		}
		void RequestLineParse()		//解析请求行
		{
			stringstream ss(request_line);
			ss>>method>>uri>>version;//自动分离
			//将方法转换为大写
			Util::StringToUpper(method);
			cout<<"method: "<<method<<endl;
			cout<<"uri: "<<uri<<endl;
			cout<<"verion: "<<version<<endl;
		}
		//解析请求报头
		void RequestHeaderParse()
		{
			std::vector<std::string> v;
			Util::TransfromVector(request_header,v);
			string key,value;
			for(int i = 0;i < v.size();++i)
			{
				Util::MakeKV(v[i],key,value);
				um.insert(make_pair(key,value));
			}
		}
		//获取请求正文长度
		int GetContentLength()
		{
			auto pos = um.find("Conten-Length");
			if(pos!=um.end())
				return (Util::StringToInt((pos->second)));
			return -1;
		}
		//判断是否需要读取请求正文
		bool IsNeedRecv()
		{
			if(method == "POST")
				return true;
			return false;
		}
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
		int RecvLine(string& line)//读一行,并且将所有不同格式的行分隔符都转换成'\n'
		{
			char c = 'X';
			while(c!='\n')
			{
				ssize_t s = recv(sock,&c,1,0); // \n  \r  \r\n
				if(s > 0)
				{
					if(c=='\r') //行分隔符有可能是\r or \r\n
					{
						if(recv(sock,&c,1,MSG_PEEK) > 0)//（窥探）MSG_PEEK相当于探针，可以探测出下一个内容
						{
							if(c=='\n') //确定行分隔符是\r\n
								recv(sock,&c,1,0);
							else		//确定行分隔符是\r
								c = '\n';
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
		void RecvRequestLine(HttpRequest* rq)//接收请求行
		{
			RecvLine(rq->GetRequestLine());		
		}
		void RecvRequestHeader(HttpRequest* rq)//接收请求报头
		{
			string temp;
			string& header = rq->GetRequestHeader();
			while(1)
			{
				RecvLine(temp);
				if(temp=="\n")
					break;
				header+=temp;
				temp.clear();
			}
		}
		~EndPoint()
		{
			if(sock>0)
				close(sock);
		}
};

//1.构建request，接收请求，
//2.解析request
//3.构建response
//4.
class Entry
{
	public:
		static void* HandlRequest(void* args)
		{
			int *p = (int*)args;
			int sock = *p;
			EndPoint* ep = new EndPoint(sock);
			HttpRequest* rq = new HttpRequest();
			HttpResponse* rsp = new HttpResponse();
			
			ep->RecvRequestLine(rq);	//接收请求行
			rq->RequestLineParse();		//解析请求行
			
			if(!rq->MethodIsLegal())		//判定请求方法是否合法
				goto end;

			ep->RecvRequestHeader(rq); //接收请求报头			
			rq->RequestHeaderParse();
end:
			delete p;
			delete ep;
			delete rq;
			delete rsp;
		}
};







#endif
