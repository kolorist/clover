#pragma once

#include <floral.h>

#include <commons.h>

#if defined(PLATFORM_WINDOWS)
#	include "VSOutputSink.h"
#else
#	include "ADBOutputSink.h"
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
#if defined(PLATFORM_WINDOWS)
#	define LOG_TOPIC(STR) \
	clover::SinkTopic<clover::VSOutputSinkDrainer> _clover_VSOutputSinkTopic(STR)
#else
#	define LOG_TOPIC(STR) \
	clover::SinkTopic<clover::ADBOutputSinkDrainer> _clover_ADBOutputSinkTopic(STR)
#endif
}
