#include "clover/VSOutputSink.h"

#include <Windows.h>
#include <stdio.h>

namespace clover {

thread_local VSOutputSink						s_VSOutputSink;
thread_local const_cstr							s_VSSinkTopics[MAX_SINK_TOPIC_DEPTH];
thread_local u32								s_VSCurrentTopicIdx = 0;

static floral::mutex							s_VSSinkLock;

void VSOutputSinkDrainer::DrainLog(LogLevel logLevel, const_cstr logStr)
{
	if (logLevel <= s_VSOutputSink.pm_LogLevel)
	{
		c8 sinkStr[512];
		sinkStr[0] = 0;
		for (u32 i = 0; i < s_VSCurrentTopicIdx; i++)
		{
			strcat(sinkStr, "/");
			strcat(sinkStr, s_VSSinkTopics[i]);
		}

		c8 buffer[2048];
		if (s_VSCurrentTopicIdx > 0) {
			sprintf(buffer, "[%s] [%s] [%s] %s",
					s_VSOutputSink.pm_Name,
					LogLevelStr[(s32)logLevel],
					sinkStr,
					logStr);
		} else {
			sprintf(buffer, "[%s] [%s] [/] %s",
					s_VSOutputSink.pm_Name,
					LogLevelStr[(s32)logLevel],
					logStr);
		}

		{
			floral::lock_guard g(s_VSSinkLock);
			OutputDebugStringA(buffer);
			OutputDebugStringA("\n");
		}
	}
}

void VSOutputSinkDrainer::PushTopic(const_cstr topicName)
{
	s_VSSinkTopics[s_VSCurrentTopicIdx] = topicName;
	s_VSCurrentTopicIdx++;
}

void VSOutputSinkDrainer::PopTopic()
{
	s_VSSinkTopics[s_VSCurrentTopicIdx] = nullptr;
	s_VSCurrentTopicIdx--;
}

//----------------------------------------------

void InitializeVSOutput(const_cstr name, LogLevel logLevel)
{
	strcpy(s_VSOutputSink.pm_Name, name);
	s_VSOutputSink.pm_LogLevel = logLevel;
}

}
