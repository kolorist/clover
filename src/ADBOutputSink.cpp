#include "ADBOutputSink.h"

#include <android/log.h>

namespace clover {

	ADBOutputSink								g_ADBOutputSink;

	static floral::mutex						s_SinkLock;

	void ADBOutputSinkDrainer::DrainLog(LogLevel i_logLevel, const_cstr i_logStr)
	{
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

		if (i_logLevel <= g_ADBOutputSink.pm_LogLevel) {
			floral::lock_guard g(s_SinkLock);
			if (g_ADBOutputSink.pm_CurrentTopicIdx > 0) {
				__android_log_print(logPrio, g_ADBOutputSink.pm_Name, "[/%s] %s",
						g_ADBOutputSink.pm_SinkTopics[g_ADBOutputSink.pm_CurrentTopicIdx - 1],
						i_logStr);
			} else {
				__android_log_print(logPrio, g_ADBOutputSink.pm_Name, "[/] %s",
						i_logStr);
			}
		}
	}

	void ADBOutputSinkDrainer::PushTopic(const_cstr i_topicName)
	{
		floral::lock_guard g(s_SinkLock);
		g_ADBOutputSink.pm_SinkTopics[g_ADBOutputSink.pm_CurrentTopicIdx] = i_topicName;
		g_ADBOutputSink.pm_CurrentTopicIdx++;
	}

	void ADBOutputSinkDrainer::PopTopic()
	{
		floral::lock_guard g(s_SinkLock);
		g_ADBOutputSink.pm_SinkTopics[g_ADBOutputSink.pm_CurrentTopicIdx] = nullptr;
		g_ADBOutputSink.pm_CurrentTopicIdx--;
	}

	//------------------------------------------
	void InitializeADBOutput(const_cstr i_name, LogLevel i_logLevel)
	{
		strcpy(g_ADBOutputSink.pm_Name, i_name);
		g_ADBOutputSink.pm_LogLevel = i_logLevel;
		g_ADBOutputSink.pm_CurrentTopicIdx = 0;
	}
	//------------------------------------------

}
