#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;

namespace RC
{
	class string
	{
		public:
			typedef char* Iterator;
		public:
			string(const char* str = "")
			{
				if(str == nullptr)
					str = "";
				_str = new char[strlen(str)+1];
				strcpy(_str,str);
				_size = strlen(str);
				_capacity = _size+1;
			}
			string(const string& s)
			{
				string temp(s._str);
				swap(_str,temp._str);
				_size = strlen(_str);
				_capacity = _size+1;
			}
			string& operator=(const string& s)
			{
				if(this != &s)
				{
					string temp(s._str);
					swap(_str,temp._str);
					swap(_size,temp._size);
					swap(_capacity,temp._size);
				}
				return *this;
			}
			~string()
			{
				if(_str)
				{
					delete _str;
					_size = 0;
				}
			}
			//iterator
			Iterator Begin()
			{
				return _str;
			}
			Iterator End()
			{
				return _str+_size;
			}
			//capacity
			size_t size()
			{
				return _size;
			}
			size_t capacity()
			{
				return _capacity;
			}
			size_t length()
			{
				return _size;
			}
			void resize(size_t newsize,char c = char())
			{
				if(newsize > _size)
				{
					if(newsize > _capacity)
					{
						reserve(newsize);
					}
					memset(_str+_size,c,newsize-_size);
				}
				_size = newsize;
				_str[newsize] = '\0';
			}
			void reserve(size_t capacity)
			{
				if(capacity > _capacity)
				{
					char* newstr = new char[capacity];
					strcpy(newstr,_str);

					delete[] _str;
					_capacity = capacity;
					_str = newstr;
				}
			}
			bool empty()
			{
				if(_str)
					return false;
				return true;
			}
			void clear()
			{
				~string();
			}
			void swap(string& s)
			{
				swap(_str,s._str);
				swap(_size,s._size);
				swap(_capacity,s._capacity);
			}
			//access
			char operator[](const int pos)
			{
				if(pos < 0 || pos >=_size)
					return nullptr;
				return _str[pos];
			}
			//modifiers
			void PushBack(char c)
			{
				if(_size == _capacity)
					reserve(2*_capacity);
				_str[_size++] = c;
			}
			void Append(size_t n,char c)
			{
				for(size_t i = 0;i<n;++i)
				{
					PushBack(c);
				}
			}
			void Append(const char* str)
			{
				for(size_t i = 0;i<strlen(str);++i)
				{
					PushBack(str[i]);
				}
			}
			string& operator+=(char c)
			{
				PushBack(c);
				return *this;
			}
			string& operator+=(const char* str)
			{
				Append(str);
				return *this;
			}
			//operator
			size_t find(char c)
			{
				for(size_t i = 0;i<_size;++i)
				{
					if(_str[i] == c)
						return i;
				}
				return -1;
			}
			char* substr(size_t start,size_t end)
			{
				if(start > _size)
					return nullptr;
				_str[end] = '\0';
				_str+=start;
				return _str;
			}
		private:
			char* _str;
			size_t _size;
			size_t _capacity;
	};
}

