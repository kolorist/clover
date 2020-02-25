#include "src/commons.cpp"
#include "src/Logger.cpp"
#if defined(FLORAL_PLATFORM_WINDOWS)
#	include "src/VSOutputSink.cpp"
#	include "src/ConsoleOutputSink.cpp"
#	include "src/Tracer.cpp"
#else
#	include "src/ADBOutputSink.cpp"
#endif
