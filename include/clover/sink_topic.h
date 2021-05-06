#pragma once

#include <floral.h>

#include "commons.h"

#if defined(FLORAL_PLATFORM_WINDOWS)
#	include "vs_output_sink.h"
#else
#	include "adb_output_sink.h"
#endif

namespace clover {

template <class TDrainer>
struct SinkTopic {
	SinkTopic(const_cstr name)
	{
		TDrainer::PushTopic(name);
	}
	
	~SinkTopic()
	{
		TDrainer::PopTopic();
	}
};

#if defined(FLORAL_PLATFORM_WINDOWS)
#	define LOG_TOPIC(STR) \
	clover::SinkTopic<clover::VSOutputSinkDrainer> _clover_VSOutputSinkTopic(STR)
#else
#	define LOG_TOPIC(STR) \
	clover::SinkTopic<clover::ADBOutputSinkDrainer> _clover_ADBOutputSinkTopic(STR)
#endif

}
