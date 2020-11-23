#include "src/commons.cpp"
#include "src/Logger.cpp"
#include "src/BufferOutputSink.cpp"
#include "src/RedirectOutputSink.cpp"
#if defined(FLORAL_PLATFORM_WINDOWS)
#	include "src/VSOutputSink.cpp"
#	include "src/ConsoleOutputSink.cpp"
#	include "src/Tracer.cpp"
#else
#	include "src/ADBOutputSink.cpp"
#endif
