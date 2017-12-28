#include "Logger.h"

#include <Windows.h>

namespace clover {
	void LogPrintStr(const_cstr str)
	{
		OutputDebugStringA(str);
	}
}
