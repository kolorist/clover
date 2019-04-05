#ifndef __CLOVER_TRACER_H__
#define __CLOVER_TRACER_H__

#include <floral.h>

namespace clover {

#define MAX_RECORDS_PER_THREAD					1000
#define MAX_RECORDS_BUNDLES						8

	struct RecorderInfo {
		u32										pm_ThreadId;
		c8										pm_Name[256];
		u32										pm_BundleIdx;
	};

	struct Record {
		c8										pm_Content[2048];
		u64										pm_TimeStamp;
	};

	struct RecordsBundle {
		Record									pm_Records[MAX_RECORDS_PER_THREAD];
		u32										pm_NextLogEntryIdx;
		u32										pm_ThreadId;
		c8										pm_Name[256];
	};

	struct RecordsKeeper {
		floral::mutex							pm_InfoLock;

		u32										pm_BundlesCount;
		RecordsBundle*							pm_Bundles[MAX_RECORDS_BUNDLES];
	};

	extern thread_local RecorderInfo			g_RecorderInfo;
	extern RecordsKeeper						g_RecordsKeeper;

	void										InitializeTracer(u32 threadId, const_cstr name);

	template <class ... Args>
	void										TracePrint(const_cstr fmt, Args... args);

	void										PrintAllTraces();
}

#include "Tracer.hpp"

#endif // __CLOVER_TRACER_H__
