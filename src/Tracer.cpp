#include "Tracer.h"

#include <stdlib.h>
#include <Windows.h>

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
				g_LinearAllocator.allocate<RecordsBundle>();
		}

		g_RecordsKeeper.pm_Bundles[g_RecorderInfo.pm_BundleIdx]->pm_NextLogEntryIdx = 0;
		g_RecordsKeeper.pm_Bundles[g_RecorderInfo.pm_BundleIdx]->pm_ThreadId = threadId;
		strcpy(g_RecordsKeeper.pm_Bundles[g_RecorderInfo.pm_BundleIdx]->pm_Name, name);
	}

	void PrintAllTraces()
	{
		// we only call this function when the program is paused
		// FIXME: the record bundles may be in incompleted state
		u32 bundlesCount = g_RecordsKeeper.pm_BundlesCount;
		u32 recordsIdx[MAX_RECORDS_BUNDLES];
		u64 minTimeStamp = ~0ull;
		s32 nextLogBundle = -1;
		memset(recordsIdx, 0, sizeof(recordsIdx));
		while (true) {
			minTimeStamp = ~0ull;
			nextLogBundle = -1;
			for (u32 i = 0; i < bundlesCount; i++) {
				// there maybe a situation when we haven't allocate record bundle yet at this point
				if (g_RecordsKeeper.pm_Bundles[i] == nullptr) continue;

				RecordsBundle& bundle = *(g_RecordsKeeper.pm_Bundles[i]);
				if (bundle.pm_Records[recordsIdx[i]].pm_TimeStamp > 0 &&
						bundle.pm_Records[recordsIdx[i]].pm_TimeStamp < minTimeStamp) {
					minTimeStamp = bundle.pm_Records[recordsIdx[i]].pm_TimeStamp;
					nextLogBundle = i;
				}
			}

			if (nextLogBundle >= 0) {
				c8 buff[2048];
				RecordsBundle& b = *(g_RecordsKeeper.pm_Bundles[nextLogBundle]);
				Record& r = b.pm_Records[recordsIdx[nextLogBundle]];
				/*
				OutputDebugStringA(g_RecordsKeeper
						.pm_Bundles[nextLogBundle]
						->pm_Records[recordsIdx[nextLogBundle]]
						.pm_Content);
				OutputDebugStringA("\n");
				*/
				sprintf(buff, "[%lld][%d][%s] %s\n", r.pm_TimeStamp, b.pm_ThreadId, b.pm_Name, r.pm_Content);
				OutputDebugStringA(buff);
				recordsIdx[nextLogBundle]++;
			} else break;
		}
	}
}
