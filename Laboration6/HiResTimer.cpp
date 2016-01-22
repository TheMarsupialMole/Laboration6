//--------------------------------------------------------------------------------------
// File: HiResTimer.cpp
//
// Measure time using QueryPerformanceCounter
//
// Copyright (c) Stefan Petersson 2011. All rights reserved.
//--------------------------------------------------------------------------------------
#include "HiResTimer.h"

HiResTimer::HiResTimer()
{
	cntsPerSec = 0;
	QueryPerformanceFrequency((LARGE_INTEGER*)&cntsPerSec);
	
	secsPerCnt = 1.0f / (float)cntsPerSec;

	/*
	Some dual core systems have a problem where the different CPUs return different
	QueryPerformanceCounter values. So when this thread is schedule on the other CPU
	in a later frame, we could even get a negative frameTime. To solve this we force
	the main thread to always run on CPU 0.
	*/
	SetThreadAffinityMask(GetCurrentThread(), 1);
}

void HiResTimer::Start()
{
	startTimeStamp = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&startTimeStamp);
}

void HiResTimer::Stop()
{
	stopTimeStamp = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&stopTimeStamp);
}

double HiResTimer::GetDeltaTime()
{
	return (stopTimeStamp - startTimeStamp) * secsPerCnt;
}