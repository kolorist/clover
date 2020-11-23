#include "clover/BufferOutputSink.h"

namespace clover
{

static floral::mutex							s_BufferSinkLock;
BufferOutputSink								s_BufferOutputSink;

thread_local const_cstr							s_BufferSinkTopics[MAX_SINK_TOPIC_DEPTH];
thread_local u32								s_BufferCurrentTopicIdx = 0;

void BufferOutputSinkDrainer::DrainLog(LogLevel logLevel, const_cstr logStr)
{
	if (logLevel <= s_BufferOutputSink.pm_LogLevel)
	{
		c8 sinkStr[512];
		sinkStr[0] = 0;
		for (u32 i = 0; i < s_BufferCurrentTopicIdx; i++)
		{
			strcat(sinkStr, "/");
			strcat(sinkStr, s_BufferSinkTopics[i]);
		}

		BufferLogEntry logEntry;
		logEntry.Level = logLevel;

		if (s_BufferCurrentTopicIdx > 0)
		{
			sprintf(logEntry.Content, "[%s] [%s] [%s] %s",
					s_BufferOutputSink.pm_Name,
					LogLevelStr[(s32)logLevel],
					sinkStr,
					logStr);
		}
		else
		{
			sprintf(logEntry.Content, "[%s] [%s] [/] %s",
					s_BufferOutputSink.pm_Name,
					LogLevelStr[(s32)logLevel],
					logStr);
		}

		{
			floral::lock_guard g(s_BufferSinkLock);
			// FIXME: this trigger memory copy
			s_BufferOutputSink.LogBuffer.push_back(logEntry);
		}
	}
}

void BufferOutputSinkDrainer::PushTopic(const_cstr topicName)
{
	s_BufferSinkTopics[s_BufferCurrentTopicIdx] = topicName;
	s_BufferCurrentTopicIdx++;
}

void BufferOutputSinkDrainer::PopTopic()
{
	s_BufferSinkTopics[s_BufferCurrentTopicIdx] = nullptr;
	s_BufferCurrentTopicIdx--;
}

// ----------------------------------------------

void InitializeBufferOutput(const_cstr name, LogLevel logLevel)
{
	strcpy(s_BufferOutputSink.pm_Name, name);
	s_BufferOutputSink.pm_LogLevel = logLevel;

	s_BufferOutputSink.LogBuffer.init(&g_LinearAllocator);
}

}
