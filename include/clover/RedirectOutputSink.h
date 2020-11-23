#pragma once

#include <floral/stdaliases.h>
#include <floral/function/simple_callback.h>

#include "Sink.h"

namespace clover
{

struct RedirectOutputSink : Sink
{
	floral::simple_callback<void, const_cstr>	Redirector;
};

struct RedirectOutputSinkDrainer
{
	static void									DrainLog(LogLevel logLevel, const_cstr logStr);
	static void									PushTopic(const_cstr topicName);
	static void									PopTopic();
};

//-----------------------------------------------
void											InitializeRedirectOutput(const_cstr name, LogLevel logLevel);
void											SetupRedirector(floral::simple_callback<void, const_cstr> redirector);

}
