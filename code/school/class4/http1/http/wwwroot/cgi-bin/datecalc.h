#ifndef _DATECALC_H_
#define _DATECALC_H_

#include <iostream>

using namespace std;

int MonthDay[13] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

class datecalc{
	
	friend ostream& operator<<(ostream& out, const datecalc& d);
	public:
		datecalc(int year, int month, int day);
		datecalc(const datecalc& d);
		datecalc operator+(int day);
		datecalc operator+=(int day);
		datecalc operator-(int day);
		datecalc operator-=(int day);
		int operator-(const datecalc& d);
		datecalc operator++();
		datecalc operator--();

		bool operator==(const datecalc& d2);
		bool operator!=(const datecalc& d2);
		bool operator>(const datecalc& d);
		bool operator>=(const datecalc& d);
		~datecalc();


	private:
		int _year;
		int _month;
		int _day;
};

#endif 
