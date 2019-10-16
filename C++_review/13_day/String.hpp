#include<iostream>
#include<string.h>
#include<assert.h>
using namespace std;

class String
{
	public:
		String(char* str = "")
		{
			if(str== nullptr)
				str="";
			_str = new char[strlen(str)+1];
			strcpy(str,_str);
			_size = strlen(str);
			_capacity = _size+1;
		}
		String(const String& s)
		{
		//	assert(s);
			_str = new char[strlen(s._str)+1];
			strcpy(s._str,_str);
			_size = strlen(_str);
			_capacity = _size+1;
		}
		String& operator=(const String& s)
		{
			if(this != &s)
			{	
				char* str = new char[strlen(s._str)+1];
				strcpy(s._str,str);
				delete _str;
				_str = str;
				_size = strlen(s._str);
				_capacity = _size+1;
			}
			return *this;
		}
		size_t Size()
		{
			return _size;
		}
		size_t Capacity()
		{
			return _capacity;
		}
		bool Empty()const
		{
			if(_str == nullptr)
				return true;
			return false;
		}

		~String()
		{
			if(_str)
			{
				delete _str;
			}
		}
	private:
		char* _str;
		size_t _size;
		size_t _capacity;
};
