#ifndef __CLOVER_LOGGER_H__
#define __CLOVER_LOGGER_H__

#include <floral.h>

#include "commons.h"

namespace clover {

	void										Initialize();

	template <class ... Args>
	void										LogPrintln(LogLevel logLevel, const_cstr fmt, Args ... args);

	void										LogPrintln(LogLevel i_logLevel, const_cstr i_str);

	void										LogPrintStr(LogLevel logLevel, const_cstr str);
}

#include "Logger.hpp"

#if 0
#define CLOVER_VERBOSE(FMT, ...)				clover::LogPrintln(clover::LogLevel::Verbose, FMT, __VA_ARGS__)
#define CLOVER_DEBUG(FMT, ...)					clover::LogPrintln(clover::LogLevel::Debug, FMT, __VA_ARGS__)
#define CLOVER_INFO(FMT, ...)					clover::LogPrintln(clover::LogLevel::Info, FMT, __VA_ARGS__)
#define CLOVER_ERROR(FMT, ...)					clover::LogPrintln(clover::LogLevel::Error, FMT, __VA_ARGS__)
#endif
#define CLOVER_VERBOSE(...)						clover::LogPrintln(clover::LogLevel::Verbose, __VA_ARGS__)
#define CLOVER_DEBUG(...)						clover::LogPrintln(clover::LogLevel::Debug, __VA_ARGS__)
#define CLOVER_INFO(...)						clover::LogPrintln(clover::LogLevel::Info, __VA_ARGS__)
#define CLOVER_ERROR(...)						clover::LogPrintln(clover::LogLevel::Error, __VA_ARGS__)

#endif // __CLOVER_LOGGER_H__
