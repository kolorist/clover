#include "clover/redirect_output_sink.h"

#include <Windows.h>
#include <stdio.h>

namespace clover
{

RedirectOutputSink								s_RedirectOutputSink;
thread_local const_cstr							s_RedirectSinkTopics[MAX_SINK_TOPIC_DEPTH];
thread_local u32								s_RedirectCurrentTopicIdx = 0;

static floral::mutex							s_RedirectSinkLock;

void RedirectOutputSinkDrainer::DrainLog(LogLevel logLevel, const_cstr logStr)
{
	if (logLevel <= s_RedirectOutputSink.pm_LogLevel)
	{
		c8 sinkStr[512];
		sinkStr[0] = 0;
		for (u32 i = 0; i < s_RedirectCurrentTopicIdx; i++)
		{
			strcat(sinkStr, "/");
			strcat(sinkStr, s_RedirectSinkTopics[i]);
		}

		c8 buffer[2048];
		if (s_RedirectCurrentTopicIdx > 0) {
			sprintf(buffer, "[%s] [%s] [%s] %s",
					s_RedirectOutputSink.pm_Name,
					LogLevelStr[(s32)logLevel],
					sinkStr,
					logStr);
		} else {
			sprintf(buffer, "[%s] [%s] [/] %s",
					s_RedirectOutputSink.pm_Name,
					LogLevelStr[(s32)logLevel],
					logStr);
		}

		{
			floral::lock_guard g(s_RedirectSinkLock);
			if (s_RedirectOutputSink.Redirector.was_bounded())
			{
				s_RedirectOutputSink.Redirector(buffer);
			}
		}
	}
}

void RedirectOutputSinkDrainer::PushTopic(const_cstr topicName)
{
	s_RedirectSinkTopics[s_RedirectCurrentTopicIdx] = topicName;
	s_RedirectCurrentTopicIdx++;
}

void RedirectOutputSinkDrainer::PopTopic()
{
	s_RedirectSinkTopics[s_RedirectCurrentTopicIdx] = nullptr;
	s_RedirectCurrentTopicIdx--;
}

//----------------------------------------------

void InitializeRedirectOutput(const_cstr name, LogLevel logLevel)
{
	floral::lock_guard g(s_RedirectSinkLock);
	strcpy(s_RedirectOutputSink.pm_Name, name);
	s_RedirectOutputSink.pm_LogLevel = logLevel;
//	s_RedirectOutputSink.Redirector = nullptr;
}

void SetupRedirector(floral::simple_callback<void, const_cstr> redirector)
{
	floral::lock_guard g(s_RedirectSinkLock);
	s_RedirectOutputSink.Redirector = redirector;
}

}
