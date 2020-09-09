#include "common.h"

#include <algorithm>

namespace
{
	std::string str(const std::string &w)
	{
		std::string s = w;
		std::sort(s.begin(), s.end());
		return s;
	}
}

void cipher3()
{
	constexpr uint32 cypherIndex = 3;

	std::string i = readInput(cypherIndex);
	i = replaceLfToSpaces(i);
	i = replaceCzech(i);
	i = toLower(i);
	i += " ";

	std::string s;
	s.reserve(i.size() + 10);
	std::string w;
	for (const char c : i)
	{
		if (c >= 'a' && c <= 'z')
		{
			w += c;
		}
		else
		{
			if (!w.empty())
				s += str(w);
			s += c;
			w = "";
		}
	}
	replace(s, " ", "");
	s = toUpper(s);

	const std::string o = generateHeader(cypherIndex) + s + generateFooter(cypherIndex);
	writeOutput(cypherIndex, o);
}

