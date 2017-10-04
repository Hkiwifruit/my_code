#include "datecalc.h"

int GetmonthDay(int year, int month)
{
	if((month == 2) && ((year%4 == 0)&&(year % 100 != 0))\
			|| (year % 400 == 0))
		return MonthDay[month]+1;
	else
		return MonthDay[month];
}

bool Islegal(int year, int month, int day)
{
	if (((month >= 1) && (month <= 12)) && \
			((day >= 1) && (day <= GetmonthDay(year, month))))
		return true;
	return false;
}

datecalc::datecalc(int year = 1990, int month = 1, int day = 1)
	: _year(year)
	  ,_month(month)
	  ,_day(day)
{}

datecalc::datecalc(const datecalc& d)
	:_year(d._year)
	 ,_month(d._month)
	 ,_day(d._day)
{}

bool datecalc::operator==(const datecalc& d2)
{
	if(_year == d2._year &&\
	   _month == d2._month &&\
	   _day == d2._day)
		return true;
}

bool datecalc::operator!=(const datecalc& d)
{

	return this->_year != d._year || \
		   this->_month != d._month || \
		   this->_day != d._day;
}

bool datecalc::operator>(const datecalc& d)
{
	if (this->_year > d._year)
		return true;
	else if (this->_year == d._year&&this->_month > d._month)
		return true;
	else if (this->_year == d._year&&this->_month ==\
			d._month&&this->_day > d._day)
		return true;
	else
		return false;
}
bool datecalc::operator>=(const datecalc& d)
{
	return *this > d ||*this == d;
}


datecalc datecalc::operator-(int day)
{
	if (day < 0){
		return *this + (-day);
	}
	datecalc tmp = *this;
	tmp._day -= day;
	while (!Islegal(tmp._year, tmp._month, tmp._day)){
		tmp._month -= 1;
		if (tmp._month < 1){
			tmp._year -= 1;
			tmp._month = 12;
		}
		tmp._day += GetmonthDay(tmp._year, tmp._month);
	}
}

datecalc datecalc::operator-=(int day)
{
	*this = *this - day;
	return *this;
}

datecalc datecalc::operator+(int day)
{
	if (day < 0){
		return *this - (-day);
	}
	datecalc tmp = *this;
	tmp._day += day;
	while (!Islegal(tmp._year, tmp._month, tmp._day)){
		tmp._day -= GetmonthDay(tmp._year, tmp._month);
		tmp._month += 1;
		if (tmp._month > 12){
			tmp._year += 1;
			tmp._month = 1;
		}
	}
	return tmp;
}

datecalc datecalc::operator+=(int day)
{
	*this = *this + day;
	return *this;
}

int datecalc::operator-(const datecalc& d)
{
	datecalc min = *this;
	datecalc max = d;
	int count = 0;
	int flag = -1;
	if (*this>d){
		max = *this;
		min = d;
		flag = 1;
	}
	while (min != max){
		min+=1;
		count++;
	}
	return count*flag;
}

datecalc datecalc::operator++()
{
	*this = *this + 1;
	return *this;
}

datecalc datecalc::operator--()
{
	*this = *this - 1;
	return *this;
}

ostream& operator<<(ostream& out, const datecalc& d)
{
	out<<d._year<<"-"<<d._month<<"-"<<d._day<<"<br>";
	return out;
}

datecalc::~datecalc()
{}


//int main()
//{
//	datecalc d1(2017, 8, 29);
//	datecalc d2(2017, 7, 22);
//	cout<<d1-d2<<endl;
//	return 0;
//}
