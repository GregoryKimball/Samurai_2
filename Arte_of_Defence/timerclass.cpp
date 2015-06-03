///////////////////////////////////////////////////////////////////////////////
// Filename: timerclass.cpp
///////////////////////////////////////////////////////////////////////////////
#include "timerclass.h"


TimerClass::TimerClass()
{
}


TimerClass::TimerClass(const TimerClass& other)
{
}


TimerClass::~TimerClass()
{
}

//The Initialize function will first query the system to see if it supports high frequency timers. If it returns a frequency then we use that value to determine how many counter ticks will occur each millisecond. We can then use that value each frame to calculate the frame time. At the end of the Initialize function we query for the start time of this frame to start the timing.

bool TimerClass::Initialize()
{
	// Check to see if this system supports high performance timers.
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_frequency);
	if(m_frequency == 0)
	{
		return false;
	}

	// Find out how many times the frequency counter ticks every millisecond.
	m_ticksPerMs = (float)(m_frequency / 1000);

	QueryPerformanceCounter((LARGE_INTEGER*)&m_startTime);

	return true;
}

//The Frame function is called for every single loop of execution by the main program. This way we can calculate the difference of time between loops and determine the time it took to execute this frame. We query, calculate, and then store the time for this frame into m_frameTime so that it can be used by any calling object for synchronization. We then store the current time as the start of the next frame.

void TimerClass::Frame()
{
	INT64 currentTime;
	float timeDifference;


	QueryPerformanceCounter((LARGE_INTEGER*)& currentTime);

	timeDifference = (float)(currentTime - m_startTime);

	m_frameTime = timeDifference / m_ticksPerMs;

	m_startTime = currentTime;

	return;
}

//GetTime returns the most recent frame time that was calculated.

float TimerClass::GetTime()
{
	return m_frameTime;
}
