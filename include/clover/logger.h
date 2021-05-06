#pragma once

#include <floral.h>

#include "commons.h"

namespace clover {

	void										Initialize(const_cstr name, LogLevel logLevel);

	template <class ... Args>
	void										LogPrintln(LogLevel logLevel, const_cstr fmt, Args ... args);

	void										LogPrintln(LogLevel i_logLevel, const_cstr i_str);

	void										LogPrintStr(LogLevel logLevel, const_cstr str);

}

#include "Logger.hpp"

#define CLOVER_VERBOSE(...)						clover::LogPrintln(clover::LogLevel::Verbose, __VA_ARGS__)
#define CLOVER_DEBUG(...)						clover::LogPrintln(clover::LogLevel::Debug, __VA_ARGS__)
#define CLOVER_INFO(...)						clover::LogPrintln(clover::LogLevel::Info, __VA_ARGS__)
#define CLOVER_WARNING(...)						clover::LogPrintln(clover::LogLevel::Warning, __VA_ARGS__)
#define CLOVER_ERROR(...)						clover::LogPrintln(clover::LogLevel::Error, __VA_ARGS__)

#define CLOVER_INIT_THIS_THREAD(name, logLevel)	clover::Initialize(name, logLevel)
