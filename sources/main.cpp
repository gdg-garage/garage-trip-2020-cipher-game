#include <cage-core/logger.h>

#include "common.h"

void cipher1();
void cipher2();

int main(int argc, const char *args[])
{
	try
	{
		// log to console
		Holder<Logger> log1 = newLogger();
		log1->format.bind<logFormatConsole>();
		log1->output.bind<logOutputStdOut>();

		CAGE_LOG(SeverityEnum::Info, "paths", stringizer() + "input path: " + inputPath);
		CAGE_LOG(SeverityEnum::Info, "paths", stringizer() + "output path: " + outputPath);

		cipher1();
		cipher2();

		return 0;
	}
	catch (...)
	{
		detail::logCurrentCaughtException();
	}
	return 1;
}
