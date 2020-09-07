#include "common.h"

void cipher1()
{
	const std::string i = readInput(1);
	const std::string o = generateHeader(1) + i + generateFooter(1);
	writeOutput(1, o);
}

