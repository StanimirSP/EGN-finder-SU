#ifndef DATE_H
#define DATE_H

#include <string>

class Date
{
	unsigned short year;
	unsigned char month;
	unsigned char day;
	bool isLeapYear() const noexcept;
	unsigned lastValidDay() const;
public:
	Date(unsigned year, unsigned month, unsigned day);
	Date(const char* YYYYMMDD);
	unsigned Year() const noexcept;
	unsigned Month() const noexcept;
	unsigned Day() const noexcept;
	bool operator<(const Date& d) const noexcept;
	bool operator<=(const Date& d) const noexcept;
	bool operator>(const Date& d) const noexcept;
	bool operator>=(const Date& d) const noexcept;
	bool operator==(const Date& d) const noexcept;
	bool operator!=(const Date& d) const noexcept;

	/**
	  * get std::string representation of a date according to format:
		Y - year (YYYY) with leading zeros
		M - month (MM) with leading zeros
		D - day (DD) with leading zeros
		y - year without leading zeros
		m - month without leading zeros
		d - day without leading zeros
		any other character is copied to the output std::string literally
	*/
	std::string date(const char* format = "Y-M-D") const;
};

#endif // DATE_H
