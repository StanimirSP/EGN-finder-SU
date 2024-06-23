#include "Date.h"
#include <limits>
#include <stdexcept>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <charconv>
#include <system_error>

Date::Date(unsigned year, unsigned month, unsigned day):
	year(year>0 && year<=9999 ? year : throw std::invalid_argument("invalid date: year too big")),
	month(month>0 && month<=12 ? month : throw std::invalid_argument("invalid date: month too big or too small")),
	day(day>0 && day<=lastValidDay() ? day : throw std::invalid_argument("invalid date: day too big or too small")) {}

Date::Date(const char* YYYYMMDD)
{
	if(std::strlen(YYYYMMDD) != 8) throw std::invalid_argument("bad date representation");
	if(std::from_chars(YYYYMMDD, YYYYMMDD+4, year).ec != std::errc{} ||
	   std::from_chars(YYYYMMDD+4, YYYYMMDD+6, month).ec != std::errc{} ||
	   std::from_chars(YYYYMMDD+6, YYYYMMDD+8, day).ec != std::errc{})
		throw std::invalid_argument("bad date representation");
	if(month<1 || month>12) throw std::invalid_argument("invalid date: month too big or too small");
	if(day<1 || day>lastValidDay()) throw std::invalid_argument("invalid date: day too big or too small");
}

bool Date::isLeapYear() const noexcept
{
	return !(year % 400) || (!(year % 4) && year % 100);
}

unsigned Date::lastValidDay() const
{
	switch(month)
	{
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		return 31;
	case 4: case 6: case 9: case 11:
		return 30;
	case 2:
		return 28+isLeapYear();
	default:
		throw std::runtime_error("unexpected error");
	}
}

unsigned Date::Year() const noexcept
{
	return year;
}

unsigned Date::Month() const noexcept
{
	return month;
}

unsigned Date::Day() const noexcept
{
	return day;
}

bool Date::operator<(const Date& d) const noexcept
{
	if(year != d.year) return year < d.year;
	if(month != d.month) return month < d.month;
	return day < d.day;
}

bool Date::operator<=(const Date& d) const noexcept
{
	return !(d < *this);
}

bool Date::operator>(const Date& d) const noexcept
{
	return d < *this;
}

bool Date::operator>=(const Date& d) const noexcept
{
	return !(*this < d);
}

bool Date::operator==(const Date& d) const noexcept
{
	return year == d.year && month == d.month && day == d.day;
}

bool Date::operator!=(const Date& d) const noexcept
{
	return !(*this == d);
}

std::string Date::date(const char* format) const
{
	std::string res;
	for(std::size_t i = 0; format[i]; i++)
	{
		char buf[5];
		switch(format[i])
		{
		case 'Y':
			std::sprintf(buf, "%04hu", year);
			break;
		case 'y':
			std::sprintf(buf, "%hu", year);
			break;
		case 'M':
			std::sprintf(buf, "%02hhu", month);
			break;
		case 'm':
			std::sprintf(buf, "%hhu", month);
			break;
		case 'D':
			std::sprintf(buf, "%02hhu", day);
			break;
		case 'd':
			std::sprintf(buf, "%hhu", day);
			break;
		default:
			res += format[i];
			continue;
		}
		res += buf;
	}
	return res;
}
