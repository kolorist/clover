#include <stdio.h>
#include <string.h>

namespace clover {
	template <class ... Args>
	void LogPrintln(LogLevel logLevel, const_cstr fmt, Args ... args)
	{
		c8 buffer[2048];
		sprintf(buffer, fmt, args...);
		strcat(buffer, "\n");
		LogPrintStr(logLevel, buffer);
	}
}
