#include "common.h"

namespace
{
}

void cipher8()
{
	constexpr uint32 cypherIndex = 8;

	std::string s = "<img src=\"data/kviz-task.png\">";

	const std::string o = generateHeader(cypherIndex) + s + generateFooter(cypherIndex);
	writeOutput(cypherIndex, o);
}

