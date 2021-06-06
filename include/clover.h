#pragma once

#include "clover/logger.h"
#include "clover/sink.h"
#include "clover/sink_topic.h"
#if defined(FLORAL_PLATFORM_WINDOWS)
#	include "clover/vs_output_sink.h"
#	include "clover/console_output_sink.h"
#	include "clover/tracer.h"
#else
#	include "clover/adb_output_sink.h"
#endif
