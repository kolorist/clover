#include "src/commons.cpp"
#include "src/logger.cpp"
#include "src/buffer_output_sink.cpp"
#include "src/redirect_output_sink.cpp"
#if defined(FLORAL_PLATFORM_WINDOWS)
#	include "src/vs_output_sink.cpp"
#	include "src/console_output_sink.cpp"
#	include "src/tracer.cpp"
#else
#	include "src/abd_output_sink.cpp"
#endif
