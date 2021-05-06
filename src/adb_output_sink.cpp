#include "clover/adb_output_sink.h"

#include <android/log.h>

namespace clover {

thread_local ADBOutputSink						s_ADBOutputSink;
thread_local const_cstr							s_ADBSinkTopics[MAX_SINK_TOPIC_DEPTH];
thread_local u32								s_ADBCurrentTopicIdx = 0;

static floral::mutex							s_ADBSinkLock;

void ADBOutputSinkDrainer::DrainLog(LogLevel i_logLevel, const_cstr i_logStr)
{
	if (i_logLevel <= s_ADBOutputSink.pm_LogLevel)
	{
		c8 sinkStr[512];
		sinkStr[0] = 0;
		for (u32 i = 0; i < s_ADBCurrentTopicIdx; i++)
		{
			strcat(sinkStr, "/");
			strcat(sinkStr, s_ADBSinkTopics[i]);
		}

		android_LogPriority logPrio = ANDROID_LOG_VERBOSE;
		switch (i_logLevel) {
			case LogLevel::Error:
				logPrio = ANDROID_LOG_ERROR;
				break;
			case LogLevel::Info:
				logPrio = ANDROID_LOG_INFO;
				break;
			case LogLevel::Debug:
				logPrio = ANDROID_LOG_DEBUG;
				break;
			case LogLevel::Verbose:
				logPrio = ANDROID_LOG_VERBOSE;
				break;
			default:
				break;
		};

		if (s_ADBCurrentTopicIdx > 0) {
			__android_log_print(logPrio, "adb", "[%s] [%s] [%s] %s",
					s_ADBOutputSink.pm_Name,
					LogLevelStr[(s32)i_logLevel],
					sinkStr,
					i_logStr);
		} else {
			__android_log_print(logPrio, "adb", "[%s] [%s] [/] %s",
					s_ADBOutputSink.pm_Name,
					LogLevelStr[(s32)i_logLevel],
					i_logStr);
		}
	}
}

void ADBOutputSinkDrainer::PushTopic(const_cstr i_topicName)
{
	s_ADBSinkTopics[s_ADBCurrentTopicIdx] = i_topicName;
	s_ADBCurrentTopicIdx++;
}

void ADBOutputSinkDrainer::PopTopic()
{
	s_ADBSinkTopics[s_ADBCurrentTopicIdx] = nullptr;
	s_ADBCurrentTopicIdx--;
}

//----------------------------------------------

void InitializeADBOutput(const_cstr i_name, LogLevel i_logLevel)
{
	strcpy(s_ADBOutputSink.pm_Name, i_name);
	s_ADBOutputSink.pm_LogLevel = i_logLevel;
}

}
