///////////////////////////////////////////////////////////////////////////////
// Filename: fpsclass.cpp
///////////////////////////////////////////////////////////////////////////////
#include "fpsclass.h"


FpsClass::FpsClass()
{
}


FpsClass::FpsClass(const FpsClass& other)
{
}


FpsClass::~FpsClass()
{
}

//The Initialize function sets all the counters to zero and starts the timer.

void FpsClass::Initialize()
{
	m_fps = 0;
	m_count = 0;
	m_startTime = timeGetTime();
	return;
}

//The Frame function must be called each frame so that it can increment the frame count by 1. If it finds that one second has elapsed then it will store the frame count in the m_fps variable. It then resets the count and starts the timer again.

void FpsClass::Frame()
{
	m_count++;
	
	//m_fps = timeGetTime() - m_startTime;
	//m_startTime = timeGetTime();	

	if(timeGetTime() >= (m_startTime + 1000))
	{
		m_fps = m_count;
		m_count = 0;		
		m_startTime = timeGetTime();	
	}  //*/
}

//GetFps returns the frame per second speed for the last second that just passed. This function should be constantly queried so the latest fps can be displayed to the screen.

int FpsClass::GetFps()
{
	return m_fps;
}
