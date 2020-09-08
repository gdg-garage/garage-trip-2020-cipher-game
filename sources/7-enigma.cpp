#include "common.h"

namespace
{
}

void cipher7()
{
	constexpr uint32 cypherIndex = 7;

	std::string i = readInput(cypherIndex);
	i = replaceLfToSpaces(i);
	i = replaceCzech(i);
	i = toUpper(i);

	// todo
	std::string s = i;

	const std::string o = generateHeader(cypherIndex) + s + generateFooter(cypherIndex);
	writeOutput(cypherIndex, o);
}

