#include "cage-core/core.h"

#include <string>

using namespace cage;

extern const string inputPath;
extern const string outputPath;

std::string readInput(uint32 index);
std::string generateHeader(uint32 index);
std::string generateFooter(uint32 index);
void writeOutput(uint32 index, const std::string &output);

std::string replaceCzech(const std::string &s);
std::string toUpper(const std::string &s);
std::string toLower(const std::string &s);
