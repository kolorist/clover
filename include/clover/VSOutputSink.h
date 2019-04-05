#ifndef __CLOVER_VSOUTPUT_SINK_H__
#define __CLOVER_VSOUTPUT_SINK_H__

#include <floral.h>

#include "Sink.h"

namespace clover {
	struct VSOutputSink : Sink {
	};

	extern VSOutputSink							g_VSOutputSink;

	struct VSOutputSinkDrainer {
		static void								DrainLog(LogLevel logLevel, const_cstr logStr);
		static void								PushTopic(const_cstr topicName);
		static void								PopTopic();
	};

	////////////////////////////////////////////
	void										InitializeVSOutput(const_cstr name, LogLevel logLevel);
	////////////////////////////////////////////
}

#endif // __CLOVER_VSOUTPUT_SINK_H__
