#include<iostream>
#include<cstring>
using namespace std;

class Date
{
	public:
	//	Date()
	//	{
	//		_year = 1900;
	//		_month = 1;
	//		_day = 1;
	//	}
		Date(int y = 1900,int m = 1,int d = 1)
			:_year(y)
			,_month(m)
			,_day(d)
		{
			cout<<"Date Init()"<<endl;
		}
		Date& operator=(const Date& d)
		{
			if(this != &d)
			{
				_year = d._year;
				_month = d._month;
				_day = d._day;
			}
			return *this;
		}
		bool operator==(const Date& d)
		{
			return _year == d._year && _month == d._month && _day == d._day;
		}
		void Display()
		{
			cout<<_year<<"-"<<_month<<"-"<<_day<<endl;
		}
		Date* operator&()
		{
			return this;
		}
		const Date* operator&()const
		{
			return this;
		}
	private:
		int _year;
		int _month;
		int _day;
};

class String
{
	public:
		String(char* str = "")
		{
			if(str == nullptr)
				str = "";
			_str = new char[strlen(str)+1];
			strcpy(_str,str);
			//_str[strlen[str]] = '\0';
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
				char* NewStr = new char[strlen(s._str)+1];
				strcpy(NewStr,s._str);
				delete[] _str;
				_str = NewStr;
			}
			return *this;
		}
		~String()
		{
			if(_str)
			{
				free(_str);
				_str = nullptr;
			}	
		}
//	friend:
//		ostream& operator<<(ostream& out,const String& s);
	private:
		char* _str;
};

//ostream& operator<<(ostream& out,const String& s)
//{
//	out<<s._str;
//	return out;
//}
//
int main()
{
	//Date d1;
	
//	String s1("Hello RC");
//	cout<<s1<<endl;
	Date d1;
	Date d2 = d1;
	d1.Display();
	d2.Display();
	cout<<(d1 == d2)<<endl;
	//String s1("Hello RC");
	//String s2(s1);
	
	return 0;
}
