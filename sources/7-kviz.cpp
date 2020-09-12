#include "common.h"

namespace
{
}

void cipher7()
{
	constexpr uint32 cypherIndex = 7;

	std::string s = "<img src=\"data/kviz-task.png\">";

	const std::string o = generateHeader(cypherIndex) + s + generateFooter(cypherIndex);
	writeOutput(cypherIndex, o);
}

