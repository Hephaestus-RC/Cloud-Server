#include<strings.h>
#include<iostream>
#include<string>
#include<string.h>

using namespace std;

int main()
{
	string strSrc = "Hello RC";
	string strDes = "Hello rC";
	if(strcasecmp(strSrc.c_str(),strDes.c_str())==0)
		cout<<strSrc<<"=="<<strDes<<endl;
	else
		cout<<strSrc<<"!="<<strDes<<endl;
//	if(stricmp(strSrc.c_str(),strDes.c_str())==0)
//		cout<<strSrc<<"=="<<strDes<<endl;
//	else
//		cout<<strSrc<<"!="<<strDes<<endl;
	return 0;
}
