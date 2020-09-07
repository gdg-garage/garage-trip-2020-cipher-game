#include "common.h"

namespace
{
	char str(const char c)
	{
		if (c >= 'a' && c <= 'z')
			return 'z' - (c - 'a');
		if (c >= 'A' && c <= 'Z')
			return 'Z' - (c - 'A');
		return c;
	}
}

void cipher2()
{
	constexpr uint32 cypherIndex = 2;

	std::string i = readInput(cypherIndex);
	i = replaceLfToSpaces(i);
	i = replaceCzech(i);

	std::string s;
	s.reserve(i.size() + 10);
	for (const char c : i)
		s += str(c);

	const std::string o = generateHeader(cypherIndex) + s + generateFooter(cypherIndex);
	writeOutput(cypherIndex, o);
}

