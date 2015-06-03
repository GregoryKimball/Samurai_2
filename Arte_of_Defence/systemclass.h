////////////////////////////////////////////////////////////////////////////////
// Filename: systemclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _SYSTEMCLASS_H_
#define _SYSTEMCLASS_H_

//Here we define WIN32_LEAN_AND_MEAN. We do this to speed up the build process, it reduces the size of the Win32 header files by excluding some of the less used APIs.

///////////////////////////////
// PRE-PROCESSING DIRECTIVES //
///////////////////////////////
#define WIN32_LEAN_AND_MEAN

//Windows.h is included so that we can call the functions to create/destroy windows and be able to use the other useful win32 functions.

//////////////
// INCLUDES //
//////////////
#include <windows.h>

//We have included the headers to the other two classes in the frame work at this point so we can use them in the system class.

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "inputclass.h"
#include "graphicsclass.h"
#include "soundclass.h"
#include "modellistclass.h"


#include "fpsclass.h"
#include "cpuclass.h"
#include "timerclass.h"
#include "positionclass.h"
#include "accelerometerclass.h"
#include "gamemodelclass.h"
#include "aiclass.h"


const int DEFAULT_WINDOW_WIDTH = 1280;
const int DEFAULT_WINDOW_HEIGHT = 1024;

//const int DEFAULT_WINDOW_WIDTH = 1368;
//const int DEFAULT_WINDOW_HEIGHT = 768;




////////////////////////////////////////////////////////////////////////////////
// Class name: SystemClass
////////////////////////////////////////////////////////////////////////////////
class SystemClass
{
public:
	SystemClass();
	SystemClass(const SystemClass&);
	~SystemClass();

	bool Initialize();
	void Shutdown();
	void Run();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();
	bool HandleInput(float);
	bool HandleAI(float);
	bool AddActor();
	bool AdvancePositions(float);
	bool SyncActorAndModel();
	bool SyncCameraAndActor();
	bool CleanUpModels();


private:
	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;

	InputClass* m_Input;
	GraphicsClass* m_Graphics;
	SoundClass* m_Sound;

	FpsClass* m_Fps;
	CpuClass* m_Cpu;
	TimerClass* m_Timer;
	PositionClass* m_Position;
	AccelerometerClass* m_Accelerometer;

	GameModelClass* m_GameModel;

	int Camera_Actor_Index;
	int Camera_Actor_Distance;
	float Camera_Actor_Angle;

	int WINDOW_WIDTH;
	int WINDOW_HEIGHT;



};


/////////////////////////
// FUNCTION PROTOTYPES //
/////////////////////////
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


/////////////
// GLOBALS //
/////////////
static SystemClass* ApplicationHandle = 0;

#endif