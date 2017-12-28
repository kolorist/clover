#ifndef __CLOVER_SINK_H__
#define __CLOVER_SINK_H__

#include <floral.h>

#include <commons.h>

namespace clover {
	struct Sink {
		c8										pm_Name[128];
		LogLevel								pm_LogLevel;
		u32										pm_CurrentTopicIdx;
		const_cstr								pm_SinkTopics[MAX_SINK_TOPIC_DEPTH];
	};
}

#endif // __CLOVER_SINK_H__
