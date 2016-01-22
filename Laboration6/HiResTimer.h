//--------------------------------------------------------------------------------------
// File: HiResTimer.h
//
// Measure time using QueryPerformanceCounter
//
// Copyright (c) Stefan Petersson 2011. All rights reserved.
//--------------------------------------------------------------------------------------
#ifndef HI_RES_TIMER__H
#define HI_RES_TIMER__H

#include <windows.h>

class HiResTimer
{
	__int64 cntsPerSec;
	__int64 startTimeStamp;
	__int64 stopTimeStamp;
	double secsPerCnt;
	double sinceStart;
	double deltaTime;

public:
	HiResTimer();

	void Start();
	void Stop();
	double GetDeltaTime();
};

#endif
