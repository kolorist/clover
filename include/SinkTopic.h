#ifndef __CLOVER_SINKTOPIC_H__
#define __CLOVER_SINKTOPIC_H__

#include <floral.h>

#include <commons.h>
#include <VSOutputSink.h>

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

#define LOG_TOPIC(STR) \
	clover::SinkTopic<clover::VSOutputSinkDrainer> _clover_VSOutputSinkTopic(STR)
}

#endif // __CLOVER_SINKTOPIC_H__
