#include<iostream>
#include<string>
#include"Util.hpp"
using namespace std;

//------------------该CGI程序执行简单的运算----------------------

int main()
{
   // cout<<"<html><head><title>--Welcome To CGI--</title></head><body>"<<endl;

    string param;
    string data1;
    string data2;
    int num1,num2;
    
    //cin>>param;
    //1.通过环境变量接收
    param = getenv("PARAMETER");
    //2.通过父进程write


    auto pos = param.find('&');
    data1 = param.substr(0,pos);
    data2 = param.substr(pos+1);

    data1 = data1.substr(data1.find('=')+1);
    data2 = data2.substr(data2.find('=')+1);
    
    num1 = Util::StringToInt(data1);
    num2 = Util::StringToInt(data2);

    cout<<"<html><head><title>CGI Result:</title></head><body>";
    cout<<"<br>";
    cout<<num1<<" + "<<num2<<" = "<<num1+num2<<endl;
    cout<<"<br>";
    cout<<num1<<" - "<<num2<<" = "<<num1-num2<<endl;
    cout<<"<br>";
    cout<<num1<<" * "<<num2<<" = "<<num1*num2<<endl;
    cout<<"<br>";
    cout<<num1<<" / "<<num2<<" = "<<num1/num2<<endl;
    
    cout<<"</body></html>";
    return 0;
}
