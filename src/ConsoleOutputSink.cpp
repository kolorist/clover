#include "ConsoleOutputSink.h"

#include <stdio.h>

namespace clover {

	ConsoleOutputSink							g_ConsoleOutputSink;

	static floral::mutex						s_ConsoleSinkLock;

	void ConsoleOutputSinkDrainer::DrainLog(LogLevel logLevel, const_cstr logStr)
	{
		if (logLevel <= g_ConsoleOutputSink.pm_LogLevel) {
			floral::lock_guard g(s_ConsoleSinkLock);
			c8 buffer[2048];
			if (g_ConsoleOutputSink.pm_CurrentTopicIdx > 0) {
				sprintf(buffer, "[%s] [/%s] [%s] %s\n",
						g_ConsoleOutputSink.pm_Name,
						g_ConsoleOutputSink.pm_SinkTopics[g_ConsoleOutputSink.pm_CurrentTopicIdx - 1],
						LogLevelStr[(s32)logLevel],
						logStr);
			} else {
				sprintf(buffer, "[%s] [/] [%s] %s\n",
						g_ConsoleOutputSink.pm_Name,
						LogLevelStr[(s32)logLevel],
						logStr);
			}
			printf(buffer);
		}
	}

	void ConsoleOutputSinkDrainer::PushTopic(const_cstr topicName)
	{
		floral::lock_guard g(s_ConsoleSinkLock);
		g_ConsoleOutputSink.pm_SinkTopics[g_ConsoleOutputSink.pm_CurrentTopicIdx] = topicName;
		g_ConsoleOutputSink.pm_CurrentTopicIdx++;
	}

	void ConsoleOutputSinkDrainer::PopTopic()
	{
		floral::lock_guard g(s_ConsoleSinkLock);
		g_ConsoleOutputSink.pm_SinkTopics[g_ConsoleOutputSink.pm_CurrentTopicIdx] = nullptr;
		g_ConsoleOutputSink.pm_CurrentTopicIdx--;
	}

	////////////////////////////////////////////
	void InitializeConsoleOutput(const_cstr name, LogLevel logLevel)
	{
		strcpy(g_ConsoleOutputSink.pm_Name, name);
		g_ConsoleOutputSink.pm_LogLevel = logLevel;
		g_ConsoleOutputSink.pm_CurrentTopicIdx = 0;
	}
	////////////////////////////////////////////
}
