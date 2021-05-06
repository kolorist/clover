#pragma once

#include "clover/Logger.h"
#include "clover/Sink.h"
#include "clover/SinkTopic.h"
#if defined(FLORAL_PLATFORM_WINDOWS)
#	include "clover/vs_output_sink.h"
#	include "clover/console_output_sink.h"
#	include "clover/Tracer.h"
#else
#	include "clover/adb_output_sink.h"
#endif
