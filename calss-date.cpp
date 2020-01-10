// Date 클래스 구현
// TODO: 윤년처리 
#include<iostream>
using namespace std;
class Date
{
	int year, month, day;
	const int days[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
  public:
	void SetDate(int _year, int _month, int _day){
		year = _year;
		month = _month;
		day = _day;
	}	
	void AddDay(int inc)
	{
		day += inc;
		month += day / days[month];
		month %= 12;
		day %= days[month];
		year += month / 12;
	}
	void AddMonth(int inc) {
		if (month + inc > 12) {
			year += inc / 12;
			month += inc % 12 ;	
		} else {
			month += inc;
		}
	}
	void AddYear(int inc) {
		year += inc;	
	}
	void GetDate(void) {
		cout << year << "년 " << month << "월 " << day << "일" <<endl;
	}
};
int main() {
	Date date = Date();
	date.SetDate(2019, 01, 18);
	date.GetDate();
	date.AddDay(11);
	date.GetDate();
	date.AddMonth(23);
	date.GetDate();	
}




