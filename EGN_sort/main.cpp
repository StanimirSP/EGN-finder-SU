#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <charconv>
#include <ranges>

constexpr std::size_t ENG_LEN = 10, REGION_BEGIN = 6, REGION_END = ENG_LEN-1;
using EGN_t = std::string;

std::vector<EGN_t> read(std::istream& is)
{
	std::vector<EGN_t> v;
	char buf[ENG_LEN+1];
	while(std::cin >> buf)
		v.emplace_back(buf);
	return v;
}

class Cmp
{
	static constexpr std::size_t REGION_FIRST_NUM_SZ = 1000;
	static inline unsigned short REGION_FIRST_NUM[REGION_FIRST_NUM_SZ];
public:
	Cmp()
	{
		if(REGION_FIRST_NUM[REGION_FIRST_NUM_SZ-1]) return;
		REGION_FIRST_NUM[0] = 0;
		REGION_FIRST_NUM[44] = 44;
		REGION_FIRST_NUM[94] = 94;
		REGION_FIRST_NUM[140] = 140;
		REGION_FIRST_NUM[170] = 170;
		REGION_FIRST_NUM[184] = 184;
		REGION_FIRST_NUM[218] = 218;
		REGION_FIRST_NUM[234] = 234;
		REGION_FIRST_NUM[282] = 282;
		REGION_FIRST_NUM[302] = 302;
		REGION_FIRST_NUM[320] = 320;
		REGION_FIRST_NUM[342] = 342;
		REGION_FIRST_NUM[378] = 378;
		REGION_FIRST_NUM[396] = 396;
		REGION_FIRST_NUM[436] = 436;
		REGION_FIRST_NUM[502] = 502;
		REGION_FIRST_NUM[528] = 528;
		REGION_FIRST_NUM[556] = 556;
		REGION_FIRST_NUM[576] = 576;
		REGION_FIRST_NUM[602] = 602;
		REGION_FIRST_NUM[624] = 624;
		REGION_FIRST_NUM[722] = 722;
		REGION_FIRST_NUM[752] = 752;
		REGION_FIRST_NUM[790] = 790;
		REGION_FIRST_NUM[822] = 822;
		REGION_FIRST_NUM[844] = 844;
		REGION_FIRST_NUM[872] = 872;
		REGION_FIRST_NUM[904] = 904;
		REGION_FIRST_NUM[926] = 926;
		for(std::size_t i = 1; i<REGION_FIRST_NUM_SZ; i++)
			if(!REGION_FIRST_NUM[i])
				REGION_FIRST_NUM[i] = REGION_FIRST_NUM[i-1];
	}
	bool operator()(const EGN_t& a, const EGN_t& b) const
	{
		unsigned short r1 = 0, r2 = 0;
		std::from_chars(a.c_str()+REGION_BEGIN, a.c_str()+REGION_END, r1);
		std::from_chars(b.c_str()+REGION_BEGIN, b.c_str()+REGION_END, r2);
		return r1-REGION_FIRST_NUM[r1] < r2-REGION_FIRST_NUM[r2];
	}
};

std::ostream& print(std::ostream& os, const std::ranges::range auto& container, char delim = '\n')
{
	for(auto&& x: container)
		os << x << delim;
	return os;
}

int main()
{
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::vector<EGN_t> v{read(std::cin)};
	std::ranges::sort(v, Cmp{});
	print(std::cout, v);
}
