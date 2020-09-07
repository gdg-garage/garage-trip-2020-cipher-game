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
