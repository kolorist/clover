#pragma once

#include <floral/stdaliases.h>

#include "Sink.h"

namespace clover {
struct ADBOutputSink : Sink {
};

struct ADBOutputSinkDrainer {
	static void								DrainLog(LogLevel i_logLevel, const_cstr i_logStr);
	static void								PushTopic(const_cstr i_topicName);
	static void								PopTopic();
};

//-----------------------------------------------
void										InitializeADBOutput(const_cstr i_name, LogLevel i_logLevel);

}
