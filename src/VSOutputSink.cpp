#include "VSOutputSink.h"

#include <Windows.h>
#include <stdio.h>

namespace clover {
	VSOutputSink								g_VSOutputSink;

	static floral::mutex						s_VSSinkLock;

	void VSOutputSinkDrainer::DrainLog(LogLevel logLevel, const_cstr logStr)
	{
		if (logLevel <= g_VSOutputSink.pm_LogLevel) {
			floral::lock_guard g(s_VSSinkLock);
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
			OutputDebugStringA("\n");
		}
	}

	void VSOutputSinkDrainer::PushTopic(const_cstr topicName)
	{
		floral::lock_guard g(s_VSSinkLock);
		g_VSOutputSink.pm_SinkTopics[g_VSOutputSink.pm_CurrentTopicIdx] = topicName;
		g_VSOutputSink.pm_CurrentTopicIdx++;
	}

	void VSOutputSinkDrainer::PopTopic()
	{
		floral::lock_guard g(s_VSSinkLock);
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
