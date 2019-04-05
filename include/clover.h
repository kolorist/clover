#pragma once

#include "clover/Logger.h"
#include "clover/Sink.h"
#include "clover/SinkTopic.h"
#if defined(PLATFORM_WINDOWS)
#	include "clover/VSOutputSink.h"
#	include "clover/ConsoleOutputSink.h"
#	include "clover/Tracer.h"
#else
#	include "clover/ADBOutputSink.h"
#endif
