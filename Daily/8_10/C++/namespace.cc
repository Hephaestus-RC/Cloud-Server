#include<iostream>
#include<assert.h>
#include<cstring>
using namespace std;

namespace RC
{

	class String
	{
		private:
			char* _str;
		public:
			String(const char* str = "")
			{
				if(str == nullptr)
					str = "";
				_str = new char[strlen(str)+1];
				strcpy(_str,str);
			}
			String(const String& s)
			{
				_str = new char[strlen(s._str)+1];
				strcpy(_str,s._str);
			}	
			String& operator=(const String& s)
			{
				if(this != &s)
				{	
					char* temp = new char[strlen(s._str)+1];
					strcpy(temp,s._str);
					delete[] _str;
					_str = temp;
				}
				return *this;
			}	
			~String()
			{
				if(_str)
					delete[] _str;
			}
		private:
			friend ostream& operator<<(ostream& _cout,const String& s);
	};
	ostream& operator<<(ostream& _cout,const String& s)
	{
		cout<<s._str;
		return _cout;
	}
}
//using RC::String;
using namespace RC;

int main()
{
	String s1("Hello RC");
	String s2;
	s2 = s1;
	String s3(s2);
	cout<<"S1 :"<<s1<<endl;
	cout<<"S2 :"<<s2<<endl;
	cout<<"S3 :"<<s3<<endl;

	return 0;
}
