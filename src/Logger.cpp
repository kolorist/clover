#include "Logger.h"

#include <VSOutputSink.h>

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

	void LogPrintStr(LogLevel logLevel, const_cstr str)
	{
		VSOutputSinkDrainer::DrainLog(logLevel, str);
	}
}
