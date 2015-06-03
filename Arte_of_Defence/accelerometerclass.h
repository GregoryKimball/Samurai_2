////////////////////////////////////////////////////////////////////////////////
// Filename: ACCELEROMETERclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _ACCELEROMETERCLASS_H_
#define _ACCELEROMETERCLASS_H_


//#include "stdafx.h"
#include "windows.h"
#include <iostream>
#include <conio.h>
//#using <mscorlib.dll>
//#using namespace System



class AccelerometerClass
{
public:
	AccelerometerClass();
	AccelerometerClass(const AccelerometerClass&);
	~AccelerometerClass();

	bool Initialize();
	void Frame();

	void GetForce(int&, int&, int&);



private:
	static const int INBUFFER_LENGTH = 20;
	char INBUFFER[INBUFFER_LENGTH];
    
	int last_x, last_y, last_z;
	int a_x, a_y, a_z;


	
    DWORD        bytes_read    ;    // Number of bytes read from port
    DWORD        bytes_written ;    // Number of bytes written to the port
    HANDLE       comport      ;  // Handle COM port
	int   bStatus;
    DCB          comSettings;          // Contains various port settings
    COMMTIMEOUTS CommTimeouts;
    

};

#endif