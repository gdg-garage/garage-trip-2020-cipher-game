#include <cage-core/logger.h>
#include <cage-core/config.h>

#include "common.h"

void cipher1();
void cipher2();
void cipher3();
void cipher4();
void cipher5();
void cipher6();
void cipher7();
void cipher8();

int main(int argc, const char *args[])
{
	try
	{
		// log to console
		Holder<Logger> log1 = newLogger();
		log1->format.bind<logFormatConsole>();
		log1->output.bind<logOutputStdOut>();

		configSetUint64("cage/random/seed1", 62989854258987);
		configSetUint64("cage/random/seed2", 5654226896534589);

		CAGE_LOG(SeverityEnum::Info, "paths", stringizer() + "input path: " + inputPath);
		CAGE_LOG(SeverityEnum::Info, "paths", stringizer() + "output path: " + outputPath);

		cipher1();
		cipher2();
		cipher3();
		cipher4();
		cipher5();
		cipher6();
		cipher7();
		cipher8();

		return 0;
	}
	catch (...)
	{
		detail::logCurrentCaughtException();
	}
	return 1;
}
