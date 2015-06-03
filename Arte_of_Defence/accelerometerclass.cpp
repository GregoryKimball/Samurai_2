///////////////////////////////////////////////////////////////////////////////
// Filename: accelerometerclass.cpp
///////////////////////////////////////////////////////////////////////////////
#include "accelerometerclass.h"


AccelerometerClass::AccelerometerClass()
{
}


AccelerometerClass::AccelerometerClass(const AccelerometerClass& other)
{
}


AccelerometerClass::~AccelerometerClass()
{
}

//The Initialize function sets all the counters to zero and starts the timer.

bool AccelerometerClass::Initialize()
{
	
	//INBUFFER_LENGTH = 20;
	//INBUFFER = new char[INBUFFER_LENGTH];
    //char OUTBUFFER[20];

	for (int i = 0; i<INBUFFER_LENGTH ; i++)
	{
		INBUFFER[i]=' ';
	}

	last_x=0, last_y=0, last_z=0;
	a_x = 0, a_y = 0, a_z = 0;

	
    bytes_read    = 0;    // Number of bytes read from port
    bytes_written = 0;    // Number of bytes written to the port
    comport      = NULL;  // Handle COM port
	int   bStatus;
    DCB          comSettings;          // Contains various port settings
    COMMTIMEOUTS CommTimeouts;

	wchar_t* port = new wchar_t[9];
	port = L"\\\\.\\COM3";


	 if ((comport = 
         CreateFile(port,                // open com5:
                    GENERIC_READ | GENERIC_WRITE, // for reading and writing
                    0,                            // exclusive access
                    NULL,                         // no security attributes
                    OPEN_EXISTING,              
                    FILE_ATTRIBUTE_NORMAL,
                    NULL)) == INVALID_HANDLE_VALUE)
    {
        // error processing code goes here
    }
    // Set timeouts in milliseconds
    CommTimeouts.ReadIntervalTimeout         = 0; 
    CommTimeouts.ReadTotalTimeoutMultiplier  = 0; 
    CommTimeouts.ReadTotalTimeoutConstant    = 1;
    CommTimeouts.WriteTotalTimeoutMultiplier = 0;
    CommTimeouts.WriteTotalTimeoutConstant   = 50;
    bStatus = SetCommTimeouts(comport,&CommTimeouts);
    if (bStatus == 0)
    {
       return false;
		// error processing code goes here
    }
    // Set Port parameters.
    // Make a call to GetCommState() first in order to fill
    // the comSettings structure with all the necessary values.
    // Then change the ones you want and call SetCommState().
    GetCommState(comport, &comSettings);
    comSettings.BaudRate = 9600;
    comSettings.StopBits = ONESTOPBIT;
    comSettings.ByteSize = 8;
    comSettings.Parity   = NOPARITY;
    comSettings.fParity  = FALSE;


    bStatus = SetCommState(comport, &comSettings);
    if (bStatus == 0)
    {
       return false; // error processing code goes here
    }

	return true;
}

//The Frame function must be called each frame so that it can increment the frame count by 1. If it finds that one second has elapsed then it will store the frame count in the m_fps variable. It then resets the count and starts the timer again.

void AccelerometerClass::Frame()
{
	
	for (int i = 0; i<INBUFFER_LENGTH ; i++)
	{
		INBUFFER[i]=' ';
	}

    bStatus = ReadFile(comport,   // Handle
            &INBUFFER,            // Incoming data
            INBUFFER_LENGTH,                  // Number of bytes to read
            &bytes_read,          // Number of bytes read
            NULL);
    if (bStatus != 0)
    {
        // error processing code goes here
    }

			


	char subbuff[5];
	int threshold = 30;
	int value = 0;

	for (int i = 0; i<INBUFFER_LENGTH ; i++)
	{

			
			
		if((INBUFFER[i]=='x' || INBUFFER[i]=='y' || INBUFFER[i]=='z') && INBUFFER[i+3] != ' ' && i<INBUFFER_LENGTH - 10)
		{
			memcpy( subbuff, &INBUFFER[i+1], 3 );
				
			value = atoi(subbuff);

			if (INBUFFER[i]=='x')
			{

				if (abs(value - last_x) > threshold)
				{
					a_x = value - last_x;					
				}
				else
				{
					a_x = 0;
				}
				last_x = (int) ((float)(value)*0.1f + 0.9f * (float)last_x);
			}
				
			if (INBUFFER[i]=='y')
			{
				if (abs(value - last_y) > threshold)
				{
					a_y = value - last_y;					
				}
				else
				{
					a_y = 0;
				}
				last_y = (int) ((float)(value)*0.1f + 0.9f * (float)last_y);	
			}
				
			if (INBUFFER[i]=='z')
			{
				if (abs(value - last_z) > threshold)
				{
					a_z = value - last_z;					
				}
				else
				{
					a_z = 0;
				}
				last_z = (int) ((float)(value)*0.1f + 0.9f * (float)last_z);	

			}
			//	last_z = (float)(atoi(subbuff))*0.01f + 0.99f * (float)last_z;				
				//last_z = atoi(subbuff)-last_z;				
		}
				
	}



}

//GetFps returns the frame per second speed for the last second that just passed. This function should be constantly queried so the latest fps can be displayed to the screen.

void AccelerometerClass::GetForce(int& x, int& y, int& z)
{
	x=a_x;
	y=a_y;
	z=a_z;
	
	return ;
}
