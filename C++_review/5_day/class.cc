#include<iostream>
using namespace std;

class Date
{
	public:
		Date(int y = 1900,int m = 1,int d = 1)
			:_year(y)
			,_month(m)
			,_day(d)
		{}
		Date(const Date& d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
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
		friend ostream& operator<<(ostream& _out,const Date& d);
		friend class Time;
	private:
		int _year;
		int _month;
		int _day;
};
ostream& operator<<(ostream& _out,const Date& d)
{
	_out<<d._year<<"-"<<d._month<<"-"<<d._day;
	return _out;
}

class Time
{
	public:
		Time(int h,int m,int s)
			:_hour(h)
			,_mintur(m)
			,_second(s)
		{}
		void SetTimeDate(int year,int month,int day)
		{
			_d._year = year;
			_d._month = month;
			_d._day = day;
			_hour = 12;
			_mintur = 12;
			_second = 12;
		}
		//friend ostream& operator << (ostream& _out,Time& t);
	private:
		int _hour;
		int _mintur;
		int _second;
		Date _d;
};
//ostream& operator<<(ostream& _out,Time& t)
//{
//	_out<<t._d._year<<"-"<<t._d._month<<"-"<<t._d._day<<" "<<t._hour<<"/"<<t._mintur<<"/"<<t._second;
//	return _out;
//}

int main()
{
//	Date d1;
//	Date d2(2019,1,1);
//	Date d3(d2);
//	cout<<d1<<endl;
//	cout<<d2<<endl;
//	cout<<d3<<endl;
	Time t(1,2,3);
	t.SetTimeDate(2019,8,16);
	//cout<<t<<endl;
	return 0;
}
