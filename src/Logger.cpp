#include "Logger.h"

#include <VSOutputSink.h>

namespace clover {
	void LogPrintStr(LogLevel logLevel, const_cstr str)
	{
		VSOutputSinkDrainer::DrainLog(logLevel, str);
	}
}
