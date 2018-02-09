#include "VSOutputSink.h"

#include <Windows.h>
#include <stdio.h>

namespace clover {
	VSOutputSink								g_VSOutputSink;

	void VSOutputSinkDrainer::DrainLog(LogLevel logLevel, const_cstr logStr)
	{
		if (logLevel <= g_VSOutputSink.pm_LogLevel) {
			static floral::mutex s_PrintLock;
			floral::lock_guard g(s_PrintLock);
			c8 buffer[2048];
			if (g_VSOutputSink.pm_CurrentTopicIdx > 0) {
				sprintf(buffer, "[%s] [/%s] [%s] %s",
						g_VSOutputSink.pm_Name,
						g_VSOutputSink.pm_SinkTopics[g_VSOutputSink.pm_CurrentTopicIdx - 1],
						LogLevelStr[(s32)logLevel],
						logStr);
			} else {
				sprintf(buffer, "[%s] [/] [%s] %s",
						g_VSOutputSink.pm_Name,
						LogLevelStr[(s32)logLevel],
						logStr);
			}
			OutputDebugStringA(buffer);
		}
	}

	void VSOutputSinkDrainer::PushTopic(const_cstr topicName)
	{
		static floral::mutex s_TopicLock;
		floral::lock_guard g(s_TopicLock);
		g_VSOutputSink.pm_SinkTopics[g_VSOutputSink.pm_CurrentTopicIdx] = topicName;
		g_VSOutputSink.pm_CurrentTopicIdx++;
	}

	void VSOutputSinkDrainer::PopTopic()
	{
		static floral::mutex s_TopicLock;
		floral::lock_guard g(s_TopicLock);
		g_VSOutputSink.pm_SinkTopics[g_VSOutputSink.pm_CurrentTopicIdx] = nullptr;
		g_VSOutputSink.pm_CurrentTopicIdx--;
	}

	////////////////////////////////////////////
	void InitializeVSOutput(const_cstr name, LogLevel logLevel)
	{
		strcpy(g_VSOutputSink.pm_Name, name);
		g_VSOutputSink.pm_LogLevel = logLevel;
		g_VSOutputSink.pm_CurrentTopicIdx = 0;
	}
	////////////////////////////////////////////
}
