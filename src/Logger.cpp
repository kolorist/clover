#include "Logger.h"

#if defined(PLATFORM_WINDOWS)
#	include <VSOutputSink.h>
#	include <ConsoleOutputSink.h>
#else
#	include <ADBOutputSink.h>
#endif

namespace clover {

	struct Initializer {
		Initializer()
		{
			Initialize();
		}

		~Initializer()
		{
		}
	};

	static Initializer s_Initializer;

	void Initialize()
	{
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
