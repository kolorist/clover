#ifndef __CLOVER_COMMONS_H__
#define __CLOVER_COMMONS_H__

#include <floral.h>

namespace clover {
	enum class LogLevel {
		Disable = 0,
		Error = 1,
		Info = 2,
		Debug = 3,
		Verbose = 4
	};

	extern const_cstr							LogLevelStr[];

#define MAX_SINK_TOPIC_DEPTH					16
}

#endif // __CLOVER_COMMONS_H__
