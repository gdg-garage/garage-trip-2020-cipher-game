#include <cage-core/logger.h>

using namespace cage;

int main(int argc, const char *args[])
{
	try
	{
		return 0;
	}
	catch (...)
	{
		detail::logCurrentCaughtException();
	}
	return 1;
}
