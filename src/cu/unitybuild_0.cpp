#include "src/commons.cpp"
#include "src/Logger.cpp"
#if defined(PLATFORM_WINDOWS)
#	include "src/VSOutputSink.cpp"
#	include "src/Tracer.cpp"
#else
#	include "src/ADBOutputSink.cpp"
#endif
