#ifndef _DATE_HPP_
#define _DATE_HPP_

#include<iostream>
#include<algorithm>
using namespace std;

class Date
{
	public:
		Date(int y = 1900,int m = 1,int d = 1)
		{
			cout<<"Date Init()"<<endl;
		}
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
		Date operator+(int days)
		{
			Date temp(*this);
			_day+=days;
			while(LeapYear(_year))
			{
				while(_day>leap[_month-1])
				{
					_day = _day-leap[_month-1];
					_month+1;
				}
				while(_month>12)
				{
					_year++;
					_month=_month-12;
				}
				if(_day < leap[_month-1] && _month < 12)
					break;
			}
			while(LeapYear(_year)==false)
			{
				while(_day>noleap[_month-1])
				{
					_day = _day-noleap[_month-1];
					_month+1;
				}
				while(_month>12)
				{
					_year++;
					_month=_month-12;
				}
				if(_day < noleap[_month-1] && _month < 12)
					break;
			}
			swap(temp._year,_year);
			swap(temp._month,_month);
			swap(temp._day,_day);

			return temp;
		}
		Date operator-(int days)
		{
			Date temp(*this);
			_day-=days;
			while(LeapYear(_year))
			{
				while(_day<=0)
				{
					_day = _day+leap[_month-1];
					_month--;
				}
				while(_month==0)
				{
					_year--;
					_month=_month+12;
				}
			}
			while(LeapYear(_year)==false)
			{
				while(_day<=0)
				{
					_day = _day+noleap[_month-1];
					_month--;
				}
				while(_month==0)
				{
					_year--;
					_month=_month+12;
				}
			}
			swap(temp._year,_year);
			swap(temp._month,_month);
			swap(temp._day,_day);

			return temp;
		}
		Date& operator++()
		{
			_day++;
			if(LeapYear(_year))
			{
				if(_day > leap[_month-1])
				{
					_day = 1;
					_month++;
				}
				if(_month>12)
				{
					_year++;
					_month = 1;
				}
			}	
			else
			{
				if(_day > noleap[_month-1])
				{
					_day = 1;
					_month++;
				}
				if(_month>12)
				{
					_year++;
					_month = 1;
				}

			}
			return *this;
		}
		Date operator++(int)
		{
			Date temp(*this);
			temp._day++;
			if(LeapYear(temp._year))
			{
				if(temp._day > leap[temp._month-1])
				{
					temp._day = 1;
					temp._month++;
				}
				if(temp._month>12)
				{
					temp._year++;
					temp._month = 1;
				}
			}	
			else
			{
				if(temp._day > noleap[temp._month-1])
				{
					temp._day = 1;
					temp._month++;
				}
				if(temp._month>12)
				{
					temp._year++;
					temp._month = 1;
				}
			}
			return temp;
			*this = temp;
		}
		Date& operator--()
		{
			_day--;
			if(LeapYear(_year))
			{
				if(_day<=0)
				{
					_day = leap[_month-2];
					_month--;
				}
				if(_month==0)
				{
					_year--;
					_month = 12;
				}
			}	
			else
			{
				if(_day <= 0)
				{
					_day = noleap[_month-2];
					_month--;
				}
				if(_month==0)
				{
					_year--;
					_month = 12;
				}
			}
			return *this;
		}
		Date operator--(int)
		{
			Date temp(*this);
			temp._day--;
			if(LeapYear(temp._year))
			{
				if(temp._day ==0 )
				{
					temp._day = leap[temp._month-2];
					temp._month--;
				}
				if(temp._month == 0)
				{
					temp._year--;
					temp._month = 12;
				}
			}	
			else
			{
				if(temp._day == 0)
				{
					temp._day = noleap[temp._month-2];
					temp._month--;
				}
				if(temp._month == 0)
				{
					temp._year--;
					temp._month = 12;
				}
			}
			return temp;
			*this = temp;
		}
		bool operator>(const Date& d)const
		{
			if(_year > d._year)
				return true;
			if(_month > d._month)
				return true;
			if(_day > d._day)
				return true;
			return false;
		}
		bool operator>=(const Date& d)const
		{
			if(_year >= d._year)
				return true;
			if(_month >= d._month)
				return true;
			if(_day >= d._day)
				return true;
			return false;

		}
		bool operator<(const Date& d)const
		{
			if(_year < d._year)
				return true;
			if(_month < d._month)
				return true;
			if(_day < d._day)
				return true;
			return false;

		}
		bool operator<=(const Date& d)const
		{
			if(_year <= d._year)
				return true;
			if(_month <= d._month)
				return true;
			if(_day <= d._day)
				return true;
			return false;

		}
		bool operator==(const Date& d)const
		{
			return  (_year==d._year && _month==d._month && _day==d._day);
		}
		bool operator!=(const Date& d)const
		{	
			return  (_year!=d._year || _month!=d._month || _day!=d._day);
		}
		void Display()
		{
			cout<<_year<<"-"<<_month<<"-"<<_day<<endl;
		}
	private:
		bool LeapYear(int year)
		{
			if((year%4==0 && year%100!=0)||(year%400==0))
				return true;
			return false;
		}
	private:
		int _year;
		int _month;
		int _day;
		int leap[12] = {31,29,31,30,31,30,31,31,30,31,30,31};
		int noleap[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
};

#endif
