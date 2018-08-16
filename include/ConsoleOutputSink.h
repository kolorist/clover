#pragma once

#include <floral.h>

#include <Sink.h>

namespace clover {
	struct ConsoleOutputSink : Sink {
	};

	extern ConsoleOutputSink					g_ConsoleOutputSink;

	struct ConsoleOutputSinkDrainer {
		static void								DrainLog(LogLevel logLevel, const_cstr logStr);
		static void								PushTopic(const_cstr topicName);
		static void								PopTopic();
	};

	////////////////////////////////////////////
	void										InitializeConsoleOutput(const_cstr name, LogLevel logLevel);
	////////////////////////////////////////////
}
