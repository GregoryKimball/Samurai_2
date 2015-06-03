////////////////////////////////////////////////////////////////////////////////
// Filename: inputclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _INPUTCLASS_H_
#define _INPUTCLASS_H_



///////////////////////////////
// PRE-PROCESSING DIRECTIVES //
///////////////////////////////
#define DIRECTINPUT_VERSION 0x0800



/////////////
// LINKING //
/////////////
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")



//////////////
// INCLUDES //
//////////////
#include <dinput.h>
#include <string>



////////////////////////////////////////////////////////////////////////////////
// Class name: InputClass
////////////////////////////////////////////////////////////////////////////////
class InputClass
{
public:
	InputClass();
	InputClass(const InputClass&);
	~InputClass();

	bool Initialize(HINSTANCE, HWND, int, int);
	void Shutdown();
	bool Frame();

	bool IsEscapePressed();
	bool IsLeftPressed();
	bool IsRightPressed();
	bool IsUpPressed();
	bool IsDownPressed();
	bool IsZPressed();
	bool IsPgUpPressed();
	bool IsPgDownPressed();

	bool IsWPressed();
	bool IsAPressed();
	bool IsSPressed();
	bool IsDPressed();
	bool IsQPressed();
	bool IsEPressed();

	bool IsCPressed();
	bool IsVPressed();
	bool IsSpacePressed();
	bool IsLCtrlPressed();

	bool InputClass::IsLBracketPressed();
	bool InputClass::IsRBracketPressed();

	bool InputClass::WasLBracketPressed();
	bool InputClass::WasRBracketPressed();


	void GetMouseLocation(int&, int&);
	void GetMouseAcceleration(float&, float&);
	void GetKeyDown(char[]);
	bool IsKeyPressed(int Key);
	bool WasKeyPressed(int Key);
	void SetInputMouse();
	void SetInputTouchscreen();

	

private:
	bool ReadKeyboard();
	bool ReadMouse();
	void ProcessInput();

private:

	

	IDirectInput8* m_directInput;
	IDirectInputDevice8* m_keyboard;
	IDirectInputDevice8* m_mouse;

	char keyList[256];

	unsigned char m_keyboardState[256];
	int m_keyboardStatus[256];
	DIMOUSESTATE m_mouseState;
	int m_mouseDevice;
	float m_mouseDivisor_x;
	float m_mouseDivisor_y;

	int m_screenWidth, m_screenHeight;
	float m_mouseX, m_mouseY;
	float v_mouseX, v_mouseY;
	float a_mouseX, a_mouseY;


	int RBracketPressed;
	int LBracketPressed;
	



};

#endif
