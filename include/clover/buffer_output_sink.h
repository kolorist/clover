#pragma once

#include <floral/stdaliases.h>
#include <floral/containers/ring_buffer.h>

#include "Sink.h"

namespace clover
{

struct BufferLogEntry
{
	c8											Content[2048];
	LogLevel									Level;
};

struct BufferOutputSink : Sink
{
	floral::ring_buffer_st<BufferLogEntry, LinearAllocator, 256>	LogBuffer;
};

struct BufferOutputSinkDrainer
{
	static void									DrainLog(LogLevel logLevel, const_cstr logStr);
	static void									PushTopic(const_cstr topicName);
	static void									PopTopic();
};

// ---------------------------------------------
void 											InitializeBufferOutput(const_cstr name, LogLevel logLevel);

}
