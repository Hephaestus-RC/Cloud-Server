#include<iostream>
#include<string.h>
using namespace std;

//DeepCopy-tradition
class String1
{
	public:
		String1(const char* str = "")
		{
			if(nullptr == str)
				str = "";
			_str = new char[strlen(str)+1];
			strcpy(_str,str);
		}
		String1(const String1& s)
			:_str(new char[strlen(s._str)+1])
		{
			strcpy(_str,s._str);
		}
		String1& operator=(const String1& s)
		{
			if(this != &s)
			{
				char* _pstr = new char[strlen(s._str)+1];
				strcpy(_pstr,s._str);
				delete _str;
				_str = _pstr;
			}
			return *this;
		}
		~String1()
		{
			if(_str)
				delete _str;
		}
	private:
		char* _str;
};

//DeepCopy-Modern
class String2
{
	public:
		String2(const char* str = "")
		{
			if(nullptr == str)
				str = "";
			_str = new char[strlen(str)+1];
			strcpy(_str,str);
		}
		String2(String2& s)
		{
			String2 Temp(s._str);
			swap(_str,Temp._str);
		}
		String2 operator=(String2 s)
		{
			if(this != &s)
			{
				swap(s._str,_str);
			}
			return *this;
		}
		~String2()
		{
			if(_str)
				delete _str;
		}
	private:
		char* _str;
};
