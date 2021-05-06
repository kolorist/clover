#pragma once

#include <floral/stdaliases.h>

#include "Sink.h"

namespace clover {

struct VSOutputSink : Sink {
};

struct VSOutputSinkDrainer {
	static void									DrainLog(LogLevel logLevel, const_cstr logStr);
	static void									PushTopic(const_cstr topicName);
	static void									PopTopic();
};

//-----------------------------------------------
void											InitializeVSOutput(const_cstr name, LogLevel logLevel);

}
