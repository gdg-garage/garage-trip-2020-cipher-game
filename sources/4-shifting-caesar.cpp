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

void cipher4()
{
	constexpr uint32 cypherIndex = 4;
	constexpr char initialKey = 'g';

	std::string i = readInput(cypherIndex);
	i = replaceLfToSpaces(i);
	i = replaceCzech(i);
	i = toLower(i);

	std::string s;
	s.reserve(i.size() + 10);
	// 0 = word
	// 1 = other
	int state = 0;
	char currentKey = initialKey - 'a';
	for (const char c : i)
	{
		if (c >= 'a' && c <= 'z')
		{
			if (state != 0)
				currentKey = (currentKey + 1) % 26;
			state = 0;
			s += ((c - 'a') + currentKey) % 26 + 'a';
		}
		else
		{
			state = 1;
			s += c;
		}
	}

	const std::string o = generateHeader(cypherIndex) + s + generateFooter(cypherIndex);
	writeOutput(cypherIndex, o);
}

