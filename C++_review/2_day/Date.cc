#include<iostream>
using namespace std;

class Date
{
	public:
		void Display()
		{
			cout<<_year<<"-"<<_month<<"-"<<_day<<endl;
		}
		void SetDate(int y,int m,int d)
		{
			_year = y;
			_month = m;
			_day = d;
		}
	private:
		int _year;
		int _month;
		int _day;
};
int main()
{
	Date d1,d2;
	d1.SetDate(2019,8,13);
	d2.SetDate(2019,8,12);
	d1.Display();
	d2.Display();
	return 0;
}
