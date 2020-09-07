#include "common.h"

#include "cage-core/files.h"
#include "cage-core/debug.h"
#include "cage-core/memoryBuffer.h"

namespace
{
	string findInputPath()
	{
		return pathToAbs(pathSearchTowardsRoot("inputs", PathTypeFlags::Directory));
	}

	string findOutputPath()
	{
		try
		{
			detail::OverrideBreakpoint ob;
			return pathToAbs(pathSearchTowardsRoot("outputs", PathTypeFlags::Directory));
		}
		catch (...)
		{
			return pathJoin(findInputPath(), "../outputs");
		}
	}
}

const string inputPath = findInputPath();
const string outputPath = findOutputPath();

std::string readInput(uint32 index)
{
	MemoryBuffer b = readFile(pathJoin(inputPath, stringizer() + index + ".txt"))->readAll();
	return std::string(b.data(), b.data() + b.size());
}

std::string generateHeader(uint32 index)
{
	std::string s = R"foo(<html>
<head>
<title>TITLE</title>
</head>
<body>
)foo";
	return s.replace(s.find("TITLE", 0), 5, string(index).c_str());
}

std::string generateFooter(uint32 index)
{
	return R"foo(
</body>
</html>
)foo";
}

void writeOutput(uint32 index, const std::string &output)
{
	auto f = writeFile(pathJoin(outputPath, stringizer() + index + ".html"));
	f->write(PointerRange<const char>(output.data(), output.data() + output.size()));
	f->close();
}

void replace(std::string &str, const std::string &what, const std::string &with)
{
	while (true)
	{
		auto it = str.find(what);
		if (it == str.npos)
			break;
		str.replace(it, what.length(), with);
	}
}

std::string replaceCzech(const std::string &s)
{
	std::string o = s;

	replace(o, "á", "a");
	replace(o, "é", "e");
	replace(o, "ě", "e");
	replace(o, "í", "i");
	replace(o, "ý", "y");
	replace(o, "ó", "o");
	replace(o, "ú", "u");
	replace(o, "ů", "u");

	replace(o, "Á", "A");
	replace(o, "É", "E");
	replace(o, "Ě", "E");
	replace(o, "Í", "I");
	replace(o, "Ý", "Y");
	replace(o, "Ó", "O");
	replace(o, "Ú", "U");
	replace(o, "Ů", "U");

	replace(o, "č", "c");
	replace(o, "ď", "d");
	replace(o, "ň", "n");
	replace(o, "ř", "r");
	replace(o, "š", "s");
	replace(o, "ť", "t");
	replace(o, "ž", "z");

	replace(o, "Č", "C");
	replace(o, "Ď", "D");
	replace(o, "Ň", "N");
	replace(o, "Ř", "R");
	replace(o, "Š", "S");
	replace(o, "Ť", "T");
	replace(o, "Ž", "Z");

	return o;
}

std::string replaceLfToSpaces(const std::string &s)
{
	std::string o = s;
	replace(o, "\n", " ");
	replace(o, "\r", " ");
	replace(o, "  ", " ");
	return o;
}

std::string toUpper(const std::string &s)
{
	std::string o;
	o.reserve(s.size());
	for (const char c : s)
	{
		if (c >= 'a' && c <= 'z')
			o += c - 'a' + 'A';
		else
			o += c;
	}
	return o;
}

std::string toLower(const std::string &s)
{
	std::string o;
	o.reserve(s.size());
	for (const char c : s)
	{
		if (c >= 'A' && c <= 'Z')
			o += c - 'A' + 'a';
		else
			o += c;
	}
	return o;
}

