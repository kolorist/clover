#ifndef __CLOVER_H__
#define __CLOVER_H__

#include "Logger.h"
#include "Sink.h"
#include "SinkTopic.h"
#if defined(PLATFORM_WINDOWS)
#	include "VSOutputSink.h"
#	include "Tracer.h"
#else
#	include "ADBOutputSink.h"
#endif

#endif // __CLOVER_H__
