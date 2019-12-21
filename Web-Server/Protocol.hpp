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
#include<sys/wait.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<sys/sendfile.h>
#include<fcntl.h>
#include<pthread.h>
#include"Util.hpp"

using namespace std;

#define DEFAULT_PATH "./wwwRoot"
#define NOTFOUND_PATH "./wwwRoot/404.html"
#define NOTFOUND_SIZE 1579

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
        bool cgi; //判断处理模式是否为CGI模式
        string sfx; //请求资源后缀
        bool done; //请求是否读完的标志
	public:
		HttpRequest()
			:request_blank("\n")
			,request_body("")
			,path(DEFAULT_PATH)
			,query_str("")
			,recource_size(0)
            ,cgi(false)
            ,sfx(".html")
            ,done(false)
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
        string GetPath()
        {
            return path;
        }
        int GetRecourceSize()
        {
            return recource_size;
        }
        string GetSuffix()
        {
            return sfx;
        }
        string GetMethod()
        {
            return method;
        }
        string GetQueryStr()
        {
            return query_str;
        }
		//判断请求方法是否合法
		bool MethodIsLegal()	
		{
			if(method!="POST" && method!="GET")
				return false;
			return true;
		}
        void SetDone(bool _done)
        {
            _done = done;
        }
        bool GetDone()
        {
            return done;
        }
		//解析请求行
		void RequestLineParse()		
		{
			stringstream ss(request_line);
			ss>>method>>uri>>version; //自动分离
			Util::StringToUpper(method); //将方法转换为大写
			//cout<<"method: "<<method<<endl;
			//cout<<"uri: "<<uri<<endl;
			//cout<<"verion: "<<version<<endl;
		}
		//解析请求报头
		void RequestHeaderParse()
		{
			vector<string> v;
			Util::TransfromVector(request_header,v);
			string key,value;
			for(size_t i = 0;i < v.size();++i)
			{
				Util::MakeKV(v[i],key,value);
				um.insert(make_pair(key,value));
			}
		}
		//解析URI（判断请求资源）
		//三种情况：1.请求方法为POST，所以uri无参数
		//			2.请求方法为GET，并且uri中含有“?”,有参数
		//			3.请求方法为GET，uri中没有”?“，无参数
        //同时判断是否使用CGI模式(带参需要)
		void UriParse()
		{
			if(method == "POST")
            {
                path += uri;
                cgi = true;  
            }
            else
			{
				auto pos = uri.find('?');
				if(pos!=string::npos)
				{
					path += uri.substr(0,pos);
					query_str += uri.substr(pos+1);
                    cgi = true;
				}
				else
					path += uri;
			}
			//如果请求的是目录，将定位到该目录下的默认文件(index.html)
			if(path[path.size()-1]=='/')
				path +="index.html";
			//cout<<"URI解析结果："<<"Path : "<<path<<" Quer_str:"<<query_str<<endl;
		}
		//判断资源路径的合法性
		bool IsPathLegal()
		{
			struct stat st;
			if(stat(path.c_str(),&st)==0)
			{
                //判断请求的资源是不是一个目录
                if(S_ISDIR(st.st_mode))
                    path+="/index.html";
                
                //判断请求的资源是不是一个可执行文件
                if((S_IXUSR & st.st_mode) || (S_IXGRP & st.st_mode) || (S_IXOTH & st.st_mode))
                    cgi = true;

                //stat(path.c_str(),&st);
			    recource_size = st.st_size;
                
                auto it = path.rfind('.');
                if(it == string::npos)
                    sfx = ".html";
                else 
                    sfx = path.substr(it);
                
               // cout<<"后缀： "<<sfx<<endl;
               // cout<<"Request Size  = "<<recource_size <<endl;
               // cout<<"IsPathLegal path: "<<path<<endl;
				return true;
			}
			return false;
		}
        bool IsCgi()
        {
            return cgi;
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
		string response_header;
		string response_blank;
		string response_body;
    private:
        int fd; //发送文件时的文件描述符(sendfile()函数需要使用)
        int recource_size; //发送文件的大小
        string suffix; //请求资源的后缀
	public:
		HttpResponse()
			:response_blank("\r\n")
		{}

        string& GetResponseLine()
        {
            return response_line;
        }
        string& GetResponseHeader()
        {
            return response_header;
        }
        string& GetResponseBlank()
        {
            return  response_blank;
        }
        string& GetResponseBody()
        {
            return response_body;
        }
        int GetFd()
        {
            return fd;
        }
        int GetRecourceSize()
        {
            return recource_size;
        }
        void MakeResponseLine(int code)
        {
            response_line = "HTTP/1.1";
            response_line += " ";
            response_line += Util::IntToString(code);
            response_line += " ";
            response_line += Util::GetStateCode(code);
            response_line += "\r\n";
        }
        void MakeResponseHeader(vector<string>& v)
        {
            auto it = v.begin();
            for(;it != v.end();++it)
            {
                response_header += *it;
                response_header += "\r\n";
            }
        }
        void MakeResponse(HttpRequest* rq,int code,bool cgi)
        {
            MakeResponseLine(code);
            vector<string> v;  //完善之后，用函数将此处封装；
            string contenttype;
            string contentlength = "Content-Length: ";
            string connection = "Connection: close"; //短链接
            if(cgi)
            {
                suffix = rq->GetSuffix();
                contenttype = Util::SuffixToCT(suffix);
                recource_size = response_body.size();
                contentlength += Util::IntToString(recource_size);
            }
            else
            {
                string path;
                if(code==200)
                {
                    path = rq->GetPath();
                    recource_size = rq->GetRecourceSize();  //获得需要发送的文件的大小
                    suffix = rq->GetSuffix(); //获取请求资源的后缀
                    contenttype = Util::SuffixToCT(suffix);
                    contentlength += Util::IntToString(recource_size);
                }
                else 
                {
                    path = NOTFOUND_PATH;
                    recource_size = NOTFOUND_SIZE;
                    contenttype = "Content-Type: text/html";
                    contentlength += Util::IntToString(recource_size);
                }
                fd = open(path.c_str(),O_RDONLY);   //获得需要发送的文件的文件描述符
            }
            cout<<"ContentLenth: "<<contentlength <<endl;
            cout<<"ContentType: "<<contenttype<<endl;
            v.push_back(contentlength);
            v.push_back(contenttype);
            v.push_back(connection);

            MakeResponseHeader(v);
        }
		~HttpResponse()
        {
            if(fd!=-1)
                close(fd);
        }
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
			//cout<<"Request-Header: "<<header<<endl;
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
			//cout<<"Request-Body: "<<body<<endl;
		}
        void SendResponse(HttpResponse* rsp,bool cgi)
        {
            string& response_line = rsp->GetResponseLine();
            string& response_header = rsp->GetResponseHeader();
            string& response_blank = rsp->GetResponseBlank();
            send(sock,response_line.c_str(),response_line.size(),0);
            send(sock,response_header.c_str(),response_header.size(),0);
            send(sock,response_blank.c_str(),response_blank.size(),0);
            
            if(cgi)
            {
                //执行cgi的发送方式
                string& response_body = rsp->GetResponseBody();
                send(sock,response_body.c_str(),response_body.size(),0);
            }
            else
            {
                int fd = rsp->GetFd();
                int recource_size = rsp->GetRecourceSize();
                sendfile(sock,fd,nullptr,recource_size);
            }
        }
        void SendNotFound(HttpResponse* rsp,HttpRequest* rq,int code)
        {
            if(rq->GetDone())//继续接收请求
            {
                RecvRequestHeader(rq);
                if(rq->IsNeedRecv())
                    RecvRequestBody(rq);
            }
            rq->SetDone(true);
            rsp->MakeResponse(rq,code,false);
            SendResponse(rsp,false);
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
        static int ProcessCGI(HttpRequest* rq,HttpResponse* rsp)
        {
            //创建子进程
            //创建管道，并且关闭无用的读写端
            //子进程通过设置环境变量，将参数设置成环境变量，
            //将子进程中的管道读写端的文件描述符进行重定向，
            //子进程进行程序替换-------> 执行CGI程序，将CGI程序的结果输出到已经被重定向的标准输出，
            //父进程将子进程创建完毕后，发送参数到子进程中，
            //父进程接收子进程的运行结果，
            //父进程等待子进程退出(waitpid())。
            int code = 200;
            string path = rq->GetPath();
            string method = rq->GetMethod();
            string parameter = "PARAMETER=" ;
            string param_size = "PARAMSIZE=";
            if(method == "POST")
                parameter += rq->GetRequestBody();
            else if(method == "GET")
                parameter += rq->GetQueryStr();
            param_size += Util::IntToString(parameter.size()-10);
            
            int input[2];
            int output[2];
            pipe(input);
            pipe(output);

            pid_t id = fork();
            if(id < 0)
            {
                //日志文件输入
                cout<<"Fork Error"<<endl;
                code = 500;
            }
            else if(id == 0)
            {//child
                close(input[1]);
                close(output[0]);
                dup2(input[0],0);
                dup2(output[1],1);
                putenv((char*)parameter.c_str()); //传入参数
                putenv((char*)param_size.c_str()); //传入参数大小
                execl(path.c_str(),path.c_str(),nullptr);
                exit(1);
            }
            else 
            {//father
                close(input[0]);
                close(output[1]);
                waitpid(id,nullptr,0);
                string& rspBody = rsp->GetResponseBody();
                char x;
                while(read(output[0],&x,1)>0)
                    rspBody.push_back(x);
            }
            return code;
        }

        
		static void HandlRequest(int sock)
		{
            int code = 200; //状态码
            bool cgi = true;
			EndPoint* ep = new EndPoint(sock);
			HttpRequest* rq = new HttpRequest();
			HttpResponse* rsp = new HttpResponse();
			
			ep->RecvRequestLine(rq);	//接收请 求行
			rq->RequestLineParse();		//解析请求行
			
			if(!rq->MethodIsLegal())	//判定请求方法是否合法
            {
               cout<<"错误方法为："<<rq->GetMethod()<<endl; 
                code = 400;
                cout<<"Error MethodIsLegal()"<<endl;
                goto end;
            }

			ep->RecvRequestHeader(rq);  //接收请求报头	
			rq->RequestHeaderParse();

			if(rq->IsNeedRecv())	//判断是否需要继续读(读请求正文)
				ep->RecvRequestBody(rq);

            rq->SetDone(true);
			rq->UriParse();	  //解析uri

			if(!rq->IsPathLegal())  //判断请求资源的路径是否合法
            {
                code = 404;
                cout<<"Error IsPathLegal()"<<endl;
                goto end;
            }

            cout<<"接收请求完毕："<<endl;
           
            cout<<"Path:"<<rq->GetPath()<<endl;
            //判断是否需要执行CGI模式
            cgi = rq->IsCgi();
            if(cgi)
            {
                //执行CGI模式
                code = ProcessCGI(rq,rsp);
                cout<<"CGI程序执行完毕！"<<endl;
                if(code != 200)
                {
                    cout<<"CGI error"<<endl;
                    goto end;
                }
                rsp->MakeResponse(rq,code,cgi); 
                cout<<"响应报文执行完毕！"<<endl;
                ep->SendResponse(rsp,cgi); 
                cout<<"响应发送执行完毕！"<<endl;
            }
            else
            {
                rsp->MakeResponse(rq,code,cgi);
                cout<<"响应报文执行完毕！"<<endl;
                ep->SendResponse(rsp,cgi);
                cout<<"响应发送执行完毕！"<<endl;
            }
            
end:
            cout<<"Code : "<<code<<endl;
            if(code != 200)
            {
                cout<<"Ready To Send 404"<<endl;
                ep->SendNotFound(rsp,rq,code);
                cout<<"404 页面发送完毕！"<<endl;
            }

			delete ep;
			delete rq;
			delete rsp;
		}
};







#endif
