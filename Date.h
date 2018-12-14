#include <string>
using namespace std;

class Date {
public:
	Date(int d, int m, int y);
	Date(string);
	void set_date(int d, int m, int y);
	void add_one_day();
	void print_date() const;

	int get_day() const { return day; }
	int get_month() const { return month; }
	int get_year() const { return year; }

	bool equals(const Date& d) const;
private:
	int day;
	int month;
	int year;
};

bool is_leap_year(int y);

extern const Date piruzie_enghelab;




