#ifndef __CLOVER_COMMONS_H__
#define __CLOVER_COMMONS_H__

#include <floral.h>
#include <helich.h>

namespace clover {

	// memory
	typedef helich::allocator<helich::stack_scheme, helich::no_tracking_policy>	LinearAllocator;
	// user-defined later
	extern LinearAllocator						g_LinearAllocator;

	enum class LogLevel {
		Disable = 0,
		Error = 1,
		Warning = 2,
		Info = 3,
		Debug = 4,
		Verbose = 5
	};

	extern const_cstr							LogLevelStr[];

#define MAX_SINK_TOPIC_DEPTH					16
}

#endif // __CLOVER_COMMONS_H__
