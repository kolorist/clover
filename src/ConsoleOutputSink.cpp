#include "ConsoleOutputSink.h"

#include <stdio.h>

namespace clover {

thread_local ConsoleOutputSink					s_ConsoleOutputSink;
thread_local const_cstr							s_ConsoleSinkTopics[MAX_SINK_TOPIC_DEPTH];
thread_local u32								s_ConsoleCurrentTopicIdx = 0;

static floral::mutex							s_ConsoleSinkLock;

void ConsoleOutputSinkDrainer::DrainLog(LogLevel logLevel, const_cstr logStr)
{
	if (logLevel <= s_ConsoleOutputSink.pm_LogLevel)
	{
		c8 sinkStr[512];
		sinkStr[0] = 0;
		for (u32 i = 0; i < s_ConsoleCurrentTopicIdx; i++)
		{
			strcat(sinkStr, "/");
			strcat(sinkStr, s_ConsoleSinkTopics[i]);
		}

		c8 buffer[2048];
		if (s_ConsoleCurrentTopicIdx > 0) {
			sprintf(buffer, "[%s] [%s] [%s] %s\n",
					s_ConsoleOutputSink.pm_Name,
					LogLevelStr[(s32)logLevel],
					sinkStr,
					logStr);
		} else {
			sprintf(buffer, "[%s] [/] [%s] %s\n",
					s_ConsoleOutputSink.pm_Name,
					LogLevelStr[(s32)logLevel],
					logStr);
		}

		{
			floral::lock_guard g(s_ConsoleSinkLock);
			printf(buffer);
		}
	}
}

void ConsoleOutputSinkDrainer::PushTopic(const_cstr topicName)
{
	s_ConsoleSinkTopics[s_ConsoleCurrentTopicIdx] = topicName;
	s_ConsoleCurrentTopicIdx++;
}

void ConsoleOutputSinkDrainer::PopTopic()
{
	s_ConsoleSinkTopics[s_ConsoleCurrentTopicIdx] = nullptr;
	s_ConsoleCurrentTopicIdx--;
}

//----------------------------------------------

void InitializeConsoleOutput(const_cstr name, LogLevel logLevel)
{
	strcpy(s_ConsoleOutputSink.pm_Name, name);
	s_ConsoleOutputSink.pm_LogLevel = logLevel;
}

}
