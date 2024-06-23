#include <iostream>
#include <stdexcept>
#include <cstdio>
#include <cstdlib>
#include "Date.h"

int charToInt(char a)
{
	return a - '0';
}
char intToChar(int a)
{
	return a + '0';
}

char last(const char* egn)
{
	int sum = 0;
	for(int i = 8; i>=0; i--) sum = 2*(sum + charToInt(egn[i]));
	return intToChar(sum % 11 % 10);
}

std::ostream& generateEGN(std::ostream& os, Date birthdate, bool isFemale, unsigned region_begin = 0, unsigned region_end = 999)
{
	unsigned yy = birthdate.Year() % 100, mm = birthdate.Month(), dd = birthdate.Day();
	if(birthdate.Year() < 1900) mm += 20;
	else if(birthdate.Year() >= 2000) mm += 40;
	char egn[10];
	std::sprintf(egn, "%02u%02u%02u", yy, mm, dd);
	for(unsigned i = (region_begin&~1)+isFemale; i<=region_end; i += 2)
	{
		std::sprintf(egn+6, "%03u", i);
		os << egn << last(egn) << '\n';
	}
	return os;
}

bool isFemale(const char* str)
{
	if(!*str || str[1]) throw std::invalid_argument("bad gender: should be one of {m,f}");
	if(*str == 'm') return false;
	if(*str == 'f') return true;
	throw std::invalid_argument("bad gender: should be one of {m,f}");
}

int main(int argc, char** argv)
{
	if(argc < 3)
	{
		std::cerr << "Usage: " << (argc>0 ? *argv : "<program_name>") << " <birthdate: YYYYMMDD> <gender: {m,f}>\n";
		return 1;
	}
	try {
		generateEGN(std::cout, Date(argv[1]), isFemale(argv[2]), argc > 3 ? std::atoi(argv[3]) : 0, argc > 4 ? std::atoi(argv[4]) : 999);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
		return 1;
	}
}
