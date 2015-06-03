///////////////////////////////////////////////////////////////////////////////
// Filename: cpuclass.cpp
///////////////////////////////////////////////////////////////////////////////
#include "cpuclass.h"


CpuClass::CpuClass()
{
}


CpuClass::CpuClass(const CpuClass& other)
{
}


CpuClass::~CpuClass()
{
}

//The Initialize function will setup the handle for querying the cpu on its usage. The query setup here will combine the usage of all the cpus in the system and gives us back a total instead of each individual cpu's usage. If it can't get a query handle or poll the cpu usage for whatever reason it will set the m_canReadCpu flag to false and just keep the cpu usage at zero percent. Some cpus and operating systems privilege levels can cause this to fail. We also start the timer so we only sample the cpu usage once a second.

void CpuClass::Initialize()
{
	PDH_STATUS status;


	// Initialize the flag indicating whether this object can read the system cpu usage or not.
	m_canReadCpu = true;

	// Create a query object to poll cpu usage.
	status = PdhOpenQuery(NULL, 0, &m_queryHandle);
	if(status != ERROR_SUCCESS)
	{
		m_canReadCpu = false;
	}

	// Set query object to poll all cpus in the system.
	status = PdhAddCounter(m_queryHandle, TEXT("\\Processor(_Total)\\% processor time"), 0, &m_counterHandle);
	if(status != ERROR_SUCCESS)
	{
		m_canReadCpu = false;
	}

	m_lastSampleTime = GetTickCount(); 

	m_cpuUsage = 0;

	return;
}

//The Shutdown function releases the handle we used to query the cpu usage.

void CpuClass::Shutdown()
{
	if(m_canReadCpu)
	{
		PdhCloseQuery(m_queryHandle);
	}

	return;
}

//Just like the FpsClass we have to call the Frame function each frame. But to reduce the amount of querying we use a m_lastSampleTime variable to ensure we only sample once a second. So each second we ask the cpu for its usage and save that value in m_cpuUsage. More than this is not necessary.

void CpuClass::Frame()
{
	PDH_FMT_COUNTERVALUE value; 

	if(m_canReadCpu)
	{
		if((m_lastSampleTime + 1000) < GetTickCount())
		{
			m_lastSampleTime = GetTickCount(); 

			PdhCollectQueryData(m_queryHandle);
        
			PdhGetFormattedCounterValue(m_counterHandle, PDH_FMT_LONG, NULL, &value);

			m_cpuUsage = value.longValue;


		}
	}

	return;
}

//The GetCpuPercentage function returns the value of the current cpu usage to any calling function. Once again if it couldn't read the cpu for whatever reason we just set the usage to zero.

int CpuClass::GetCpuPercentage()
{
	int usage;

	if(m_canReadCpu)
	{
		usage = (int)m_cpuUsage;
	}
	else
	{
		usage = 0;
	}

	return usage;
}
