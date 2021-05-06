#if defined(FLORAL_PLATFORM_WINDOWS)
#include <intrin.h>
#else
#endif

namespace clover {
	template <class ... Args>
	void TracePrint(const_cstr fmt, Args... args)
	{
		u32 bundleIdx = g_RecorderInfo.pm_BundleIdx;
		RecordsBundle& bundle = *(g_RecordsKeeper.pm_Bundles[bundleIdx]);
		Record& record = bundle.pm_Records[bundle.pm_NextLogEntryIdx];

		sprintf(record.pm_Content, fmt, args...);

#if defined(FLORAL_PLATFORM_WINDOWS)
		record.pm_TimeStamp = __rdtsc();
#else
#endif
		bundle.pm_NextLogEntryIdx = (bundle.pm_NextLogEntryIdx + 1) % MAX_RECORDS_PER_THREAD;
	}
}
