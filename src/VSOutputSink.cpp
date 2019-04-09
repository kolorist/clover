#include "clover/VSOutputSink.h"

#include <Windows.h>
#include <stdio.h>

namespace clover {

VSOutputSink									g_VSOutputSink;
thread_local const_cstr							s_SinkTopics[MAX_SINK_TOPIC_DEPTH];
thread_local u32								s_CurrentTopicIdx = 0;

static floral::mutex							s_VSSinkLock;

void VSOutputSinkDrainer::DrainLog(LogLevel logLevel, const_cstr logStr)
{
	if (logLevel <= g_VSOutputSink.pm_LogLevel) {
		floral::lock_guard g(s_VSSinkLock);
		c8 buffer[2048];
		if (s_CurrentTopicIdx > 0) {
			sprintf(buffer, "[%s] [%s] [/%s] %s",
					g_VSOutputSink.pm_Name,
					LogLevelStr[(s32)logLevel],
					s_SinkTopics[s_CurrentTopicIdx - 1],
					logStr);
		} else {
			sprintf(buffer, "[%s] [%s] [/] %s",
					g_VSOutputSink.pm_Name,
					LogLevelStr[(s32)logLevel],
					logStr);
		}
		OutputDebugStringA(buffer);
		OutputDebugStringA("\n");
	}
}

void VSOutputSinkDrainer::PushTopic(const_cstr topicName)
{
	//floral::lock_guard g(s_VSSinkLock);
	s_SinkTopics[s_CurrentTopicIdx] = topicName;
	s_CurrentTopicIdx++;
}

void VSOutputSinkDrainer::PopTopic()
{
	//floral::lock_guard g(s_VSSinkLock);
	s_SinkTopics[s_CurrentTopicIdx] = nullptr;
	s_CurrentTopicIdx--;
}

////////////////////////////////////////////
void InitializeVSOutput(const_cstr name, LogLevel logLevel)
{
	strcpy(g_VSOutputSink.pm_Name, name);
	g_VSOutputSink.pm_LogLevel = logLevel;
}
////////////////////////////////////////////

}
