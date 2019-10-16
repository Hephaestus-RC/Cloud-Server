#include<iostream>
#include<string>
using namespace std;

void Test1()
{
	string s1;
	string s2("Hello RC");
	string s3(10,'a');
	string s4(s2);
	string s5(s3,5);
	cout<<s1<<endl;
	cout<<s2<<endl;
	cout<<s3<<endl;
	cout<<s4<<endl;
	cout<<s5<<endl;

}
void Test2()
{
	string s("Hello,RC!!!");
	cout<<s.length()<<endl;
	cout<<s.size()<<endl;
	cout<<s.capacity()<<endl;
	cout<<s<<endl;

	s.clear();
	cout<<s.size()<<endl;
	cout<<s.capacity()<<endl;

	s.resize(10,'a');
	cout<<s.size()<<endl;
	cout<<s.capacity()<<endl;


	s.resize(15);
	cout<<s.size()<<endl;
	cout<<s.capacity()<<endl;

	s.resize(5);
	cout<<s.size()<<endl;
	cout<<s<<endl;
}
void Test3()
{
	string s;
	s.reserve(100);
	cout<<s.size()<<endl;
	cout<<s.capacity()<<endl;

	s.reserve(50);
	cout<<s.size()<<endl;
	cout<<s.capacity()<<endl;
}
void Test4()
{
	string s1("Hello RC");
	const string s2("Hello RC");
	cout<<s1<<" "<<s2<<endl;
	cout<<s1[0]<<" "<<s2[0]<<endl;

	s1[0] = 'h';
	cout<<s1<<endl;

	for(size_t i = 0;i<s1.size();++i)
	{
		cout<<s1[i]<<endl;
	}
}
void Test5()
{
	string str;
	str.push_back(' ');
	str.append("Hello");
	str+='b';
	str+="it";
	cout<<str<<endl;
	cout<<str.c_str()<<endl;

	string file1("String.cpp");
	size_t pos = file1.rfind('.');
	string suffix(file1.substr(pos,file1.size()-pos));
	cout<<suffix<<endl;

	string url("http://www.cplusplus.com/reference/string/string/find/");
	cout<<url<<endl;
	size_t start = url.find("://");

	if(start == string::npos)
	{
		cout<<"invalid url"<<endl;
		return ;
	}
	start += 3;
	size_t finish = url.find('/',start);
	string address = url.substr(start,finish - start);
	cout<< address<<endl;

	pos = url.find("://");
	url.erase(0,pos+3);
	cout<<url<<endl;

}
void Test6()
{
	string s;
	size_t sz = s.capacity();
	cout<<"makeing s grow:\n";
	for(int i =0;i<100;++i)
	{
		s+='c';
		if(sz!=s.capacity())
		{
			sz = s.capacity();
			cout<<"capacity changed "<<sz<<endl;
		}
	}
}
int main()
{
	//Test1();
	//Test2();
	//Test3();
	//Test4();
	Test5();
	return 0;
}
