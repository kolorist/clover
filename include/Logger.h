#ifndef __CLOVER_LOGGER_H__
#define __CLOVER_LOGGER_H__

#include <floral.h>

namespace clover {
	void										Initialize();

	template <class ... Args>
	void LogPrintln(const_cstr fmt, Args ... args);

	void										LogPrintStr(const_cstr str);
}

#include "Logger.hpp"

#endif // __CLOVER_LOGGER_H__
