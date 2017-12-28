#ifndef __CLOVER_LOGGER_H__
#define __CLOVER_LOGGER_H__

#include <floral.h>

#include <commons.h>

namespace clover {
	void										Initialize();

	template <class ... Args>
	void LogPrintln(LogLevel logLevel, const_cstr fmt, Args ... args);

	void										LogPrintStr(LogLevel logLevel, const_cstr str);
}

#include "Logger.hpp"

#endif // __CLOVER_LOGGER_H__
