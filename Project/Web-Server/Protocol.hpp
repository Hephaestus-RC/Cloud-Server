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
#include<sys/stat.h>
#include<pthread.h>
#include"Util.hpp"

using namespace std;

#define DEFAULT_PATH "./wwwroot"

class HttpRequest
{
	private:
		string request_line; //请求行
		string request_header; //请求报头
		string request_blank; //空行
		string request_body; //请求正文
	private:
		string method; //请求方法
		string uri; //
		string version; //版本号
		unordered_map<string,string> um; //存储请求报头的条目
		string path; //资源路径
		string query_str; //传入参数
		int recource_size; //申请资源的大小
	
	public:
		HttpRequest()
			:request_blank("\n")
			,request_body("")
			,path(DEFAULT_PATH)
			,query_str("")
			,recource_size(0)
		{}
		//设置请求行
		string& GetRequestLine()	
		{
			return request_line;
		}
		//设置请求报头
		string& GetRequestHeader()	
		{
			return request_header;
		}
		//设置请求正文
		string& GetRequestBody()	
		{
			return request_body;
		}		
		//判断请求方法是否合法
		bool MethodIsLegal()	
		{
			if(method!="POST" && method!="GET")
				return false;
			return true;
		}
		//解析请求行
		void RequestLineParse()		
		{
			stringstream ss(request_line);
			ss>>method>>uri>>version; //自动分离
			Util::StringToUpper(method); //将方法转换为大写
			cout<<"method: "<<method<<endl;
			cout<<"uri: "<<uri<<endl;
			cout<<"verion: "<<version<<endl;
		}
		//解析请求报头
		void RequestHeaderParse()
		{
			vector<string> v;
			Util::TransfromVector(request_header,v);
			string key,value;
			for(int i = 0;i < v.size();++i)
			{
				Util::MakeKV(v[i],key,value);
				um.insert(make_pair(key,value));
			}
		}
		//解析URI（判断请求资源）
		void UriParse()
		{
			//三种情况：1.请求方法为POST，所以uri无参数
			//			2.请求方法为GET，并且uri中含有“?”,有参数
			//			3.请求方法为GET，uri中没有”?“，无参数
			if(method == "POST")
				path += uri; 
			else
			{
				auto pos = uri.find('?');
				if(pos!=string::npos)
				{
					path += uri.substr(0,pos);
					query_str += uri.substr(pos+1);
				}
				else
					path += uri;
			}
			//如果请求的是目录，将定位到该目录下的默认文件(index.html)
			if(path[path.size()-1]=='/')
				uri+="index.html";
			
			cout<<"URI解析结果："<<"Path : "<<path<<" Quer_str:"<<query_str<<endl;
		}
		//判断资源路径的合法性
		bool IsPathLegal()
		{
			struct stat st;
			if(stat(path.c_str(),&st)==0)
			{
				recource_size = st.st_size;
				return true;
			}
			return false;
		}
		//逐条显示请求报头的条目
		void ShowUnorderdMap()
		{
			auto it = um.begin();
			while(it!=um.end())
			{
				cout<<"key: "<<it->first<<" value: "<<it->second<<endl;
				++it;
			}
		}
		//获取请求正文长度
		int GetContentLength()
		{

			auto pos = um.find("Content-Length");
			if(pos!=um.end())
				return (Util::StringToInt(pos->second));
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
			:response_blank("\n")
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
		//接收请求行
		void RecvRequestLine(HttpRequest* rq)
		{
			RecvLine(rq->GetRequestLine());		
		}
		//接收请求报头
		void RecvRequestHeader(HttpRequest* rq)
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
			cout<<"Request-Header: "<<header<<endl;
		}
		//接收请求正文
		void RecvRequestBody(HttpRequest* rq)
		{
			
			//rq->ShowUnorderdMap();
			int len = rq->GetContentLength();
			string& body = rq->GetRequestBody();
			char c = 'X';
			for(int i = 0; i < len;++i)
			{
				if(recv(sock,&c,1,0)>0)
					body.push_back(c);
			}
			cout<<"Request-Body: "<<body<<endl;
		}
		~EndPoint()
		{
			if(sock>0)
				close(sock);
		}
};

//1. 通过EndPoint，读出请求，并构建request对象
//2. 分析request，得出请求的具体细节
//3. 构建response
//4. 通过EndPoint，将response返回给客户端，完成请求/响应的过程

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
			
			if(!rq->MethodIsLegal())	//判定请求方法是否合法
				goto end;

			ep->RecvRequestHeader(rq);  //接收请求报头	
			rq->RequestHeaderParse();

			if(rq->IsNeedRecv())	//判断是否需要继续读(读请求正文)
				ep->RecvRequestBody(rq);

			rq->UriParse();	  //解析uri

			if(!rq->IsPathLegal())
				goto end;

end:
			delete p;
			delete ep;
			delete rq;
			delete rsp;
		}
};







#endif
