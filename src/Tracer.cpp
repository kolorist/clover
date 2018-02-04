#include "Tracer.h"

#include <stdlib.h>

#include "commons.h"

namespace clover {

	thread_local RecorderInfo					g_RecorderInfo;
	RecordsKeeper								g_RecordsKeeper;

	void InitializeRecordsKeeper()
	{
		floral::lock_guard infoGuard(g_RecordsKeeper.pm_InfoLock);
		g_RecordsKeeper.pm_BundlesCount = 0;
		for (u32 i = 0; i < MAX_RECORDS_BUNDLES; i++)
			g_RecordsKeeper.pm_Bundles[i] = nullptr;
	}

	void InitializeTracer(u32 threadId, const_cstr name)
	{
		g_RecorderInfo.pm_ThreadId = threadId;
		strcpy(g_RecorderInfo.pm_Name, name);

		{
			floral::lock_guard infoGuard(g_RecordsKeeper.pm_InfoLock);
			g_RecorderInfo.pm_BundleIdx = g_RecordsKeeper.pm_BundlesCount;
			g_RecordsKeeper.pm_BundlesCount++;

			g_RecordsKeeper.pm_Bundles[g_RecorderInfo.pm_BundleIdx] =
				g_LinearAllocator.Allocate<RecordsBundle>();
		}

		g_RecordsKeeper.pm_Bundles[g_RecorderInfo.pm_BundleIdx]->pm_NextLogEntryIdx = 0;
	}

}
