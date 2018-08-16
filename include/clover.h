#pragma once

#include "Logger.h"
#include "Sink.h"
#include "SinkTopic.h"
#if defined(PLATFORM_WINDOWS)
#	include "VSOutputSink.h"
#	include "ConsoleOutputSink.h"
#	include "Tracer.h"
#else
#	include "ADBOutputSink.h"
#endif
