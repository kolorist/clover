#include "clover/Logger.h"

#if defined(PLATFORM_WINDOWS)
#	include "clover/VSOutputSink.h"
#	include "clover/ConsoleOutputSink.h"
#else
#	include "clover/ADBOutputSink.h"
#endif

namespace clover {

void Initialize(const_cstr name, LogLevel logLevel)
{
#if defined(PLATFORM_WINDOWS)
	InitializeVSOutput(name, logLevel);
	InitializeConsoleOutput(name, logLevel);
#else
	InitializeADBOutput(name, logLevel);
#endif
}

void LogPrintln(LogLevel i_logLevel, const_cstr i_str)
{
	LogPrintStr(i_logLevel, i_str);
}

void LogPrintStr(LogLevel logLevel, const_cstr str)
{
#if defined(PLATFORM_WINDOWS)
	VSOutputSinkDrainer::DrainLog(logLevel, str);
	ConsoleOutputSinkDrainer::DrainLog(logLevel, str);
#else
	ADBOutputSinkDrainer::DrainLog(logLevel, str);
#endif
}

}
