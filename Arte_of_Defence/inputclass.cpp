////////////////////////////////////////////////////////////////////////////////
// Filename: inputclass.cpp
////////////////////////////////////////////////////////////////////////////////
//#include <string.h>
#include "inputclass.h"
#include "textclass.h"
#include <string>



InputClass::InputClass()
{
	m_directInput = 0;
	m_keyboard = 0;
	m_mouse = 0;
	//m_keyDown = 0; 
//	m_accelerometer = 0;
}


InputClass::InputClass(const InputClass& other)
{
}


InputClass::~InputClass()
{
}


bool InputClass::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	HRESULT result;


	// Store the screen size which will be used for positioning the mouse cursor.
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	// Initialize the location of the mouse on the screen.
	m_mouseX = 0;
	m_mouseY = 0;
	SetInputMouse();
	//SetInputTouchscreen();
//	m_keyDown = 0;


	RBracketPressed = 0;
	LBracketPressed = 0;

	// Initialize the main direct input interface.
	result = DirectInput8Create(hinstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_directInput, NULL);
	if(FAILED(result))
	{
		return false;
	}



	// Initialize the direct input interface for the keyboard.
	result = m_directInput->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL);
	if(FAILED(result))
	{
		return false;
	}

	// Set the data format.  In this case since it is a keyboard we can use the predefined data format.
	result = m_keyboard->SetDataFormat(&c_dfDIKeyboard);
	if(FAILED(result))
	{
		return false;
	}



	// Set the cooperative level of the keyboard to not share with other programs.
	result = m_keyboard->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if(FAILED(result))
	{
		return false;
	}



	// Now acquire the keyboard.
	result = m_keyboard->Acquire();
	if(FAILED(result))
	{
		return false;
	}



	// Initialize the direct input interface for the mouse.
	result = m_directInput->CreateDevice(GUID_SysMouse, &m_mouse, NULL);
	if(FAILED(result))
	{
		return false;
	}

	// Set the data format for the mouse using the pre-defined mouse data format.
	result = m_mouse->SetDataFormat(&c_dfDIMouse);
	if(FAILED(result))
	{
		return false;
	}



	// Set the cooperative level of the mouse to share with other programs.
	//result = m_mouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	result = m_mouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if(FAILED(result))
	{
		return false;
	}



	// Acquire the mouse.
	result = m_mouse->Acquire();
	if(FAILED(result))
	{
		return false;
	}



	for(int i = 0; i<256;i++)
	{
		m_keyboardStatus[i] = 0;

	}






	return true;
}


void InputClass::SetInputMouse()
{

	m_mouseDivisor_x = 0.3f;
	m_mouseDivisor_y = 0.3f;
	m_mouseDevice = 0;
}

void InputClass::SetInputTouchscreen()
{
	m_mouseDivisor_x = 48.0f/8.0f;
	m_mouseDivisor_y = 86.0f/8.0f;
	m_mouseDevice = 1;
}



void InputClass::Shutdown()
{
	// Release the mouse.
	if(m_mouse)
	{
		m_mouse->Unacquire();
		m_mouse->Release();
		m_mouse = 0;
	}

	// Release the keyboard.
	if(m_keyboard)
	{
		m_keyboard->Unacquire();
		m_keyboard->Release();
		m_keyboard = 0;
	}

	// Release the main interface to direct input.
	if(m_directInput)
	{
		m_directInput->Release();
		m_directInput = 0;
	}

	return;
}



bool InputClass::Frame()
{
	bool result;

	


	// Read the current state of the keyboard.
	result = ReadKeyboard();
	if(!result)
	{
		return false;
	}

	// Read the current state of the mouse.
	result = ReadMouse();
	if(!result)
	{
		return false;
	}

	// Process the changes in the mouse and keyboard.
	ProcessInput();

	return true;
}



bool InputClass::ReadKeyboard()
{
	HRESULT result;

	// Read the keyboard device.
	result = m_keyboard->GetDeviceState(sizeof(m_keyboardState), (LPVOID)&m_keyboardState);
	if(FAILED(result))
	{
		// If the keyboard lost focus or was not acquired then try to get control back.
		if((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			m_keyboard->Acquire();
		}
		else
		{
			return false;
		}
	}
		




	return true;
}



bool InputClass::ReadMouse()
{
	HRESULT result;


	// Read the mouse device.
	result = m_mouse->GetDeviceState(sizeof(DIMOUSESTATE), (LPVOID)&m_mouseState);
	if(FAILED(result))
	{
		// If the mouse lost focus or was not acquired then try to get control back.
		if((result == DIERR_INPUTLOST) || (result == DIERR_NOTACQUIRED))
		{
			m_mouse->Acquire();
		}
		else
		{
			return false;
		}
	}

	return true;
}


void InputClass::ProcessInput()
{
	
	if((m_keyboardState[DIK_RBRACKET] & 0x80) && RBracketPressed == 0 )
	{		
		RBracketPressed = 1;
	}
	if(!(m_keyboardState[DIK_RBRACKET] & 0x80) && RBracketPressed == 2 )
	{		
		RBracketPressed = 0;
	}

	if((m_keyboardState[DIK_LBRACKET] & 0x80) && LBracketPressed == 0 )
	{		
		LBracketPressed = 1;
	}
	if(!(m_keyboardState[DIK_LBRACKET] & 0x80) && LBracketPressed == 2 )
	{		
		LBracketPressed = 0;
	}

	


	for(int i = 0; i<256;i++)
	{		
		if((m_keyboardState[i] & 0x80) && m_keyboardStatus[i] == 0 )
		{		
			m_keyboardStatus[i] = 1;
		}

		

		if(!(m_keyboardState[i] & 0x80) && m_keyboardStatus[i] == 2 )
		{		
			m_keyboardStatus[i] = 0;
		}

	
	}


	
	float mx = (float)m_mouseState.lX / (float) m_mouseDivisor_x;
	float my = (float)m_mouseState.lY / (float) m_mouseDivisor_y;


	// Update the location of the mouse cursor based on the change of the mouse location during the frame.



	if(m_mouseState.lX != 0 && m_mouseState.lY != 0)
	TextClass::debug_strings[16] = "m.lX  " + TextClass::GetString(m_mouseState.lX) + " :           " + 
								   "m.lY  " + TextClass::GetString(m_mouseState.lY);
	
	m_mouseX += (float) mx;
	m_mouseY += (float) my;

	v_mouseX = (float) mx;
	v_mouseY = (float) my;

	// Ensure the mouse location doesn't exceed the screen width or height.
	if((int)m_mouseX < 0)  { m_mouseX = 0.0f; }
	if((int)m_mouseY < 0)  { m_mouseY = 0.0f; }
	
	if((int)m_mouseX > m_screenWidth)  { m_mouseX = (float)m_screenWidth; }
	if((int)m_mouseY > m_screenHeight) { m_mouseY = (float)m_screenHeight; }
	
	return;
}



bool InputClass::IsEscapePressed()
{
	if(m_keyboardState[DIK_ESCAPE] & 0x80)
	{		return true;	}
	return false;
}


bool InputClass::IsLeftPressed()
{
	if(m_keyboardState[DIK_LEFT] & 0x80)
	{		return true;	}
	return false;
}

	
bool InputClass::IsRightPressed()
{
	if(m_keyboardState[DIK_RIGHT] & 0x80)
	{		return true;	}
	return false;
}

bool InputClass::IsUpPressed()
{
	if(m_keyboardState[DIK_UP] & 0x80)
	{		return true;	}
	return false;
}
bool InputClass::IsDownPressed()
{
	if(m_keyboardState[DIK_DOWN] & 0x80)
	{		return true;	}
	return false;
}
bool InputClass::IsAPressed()
{
	if(m_keyboardState[DIK_A] & 0x80)
	{		return true;	}
	return false;
}
bool InputClass::IsZPressed()
{
	if(m_keyboardState[DIK_Z] & 0x80)
	{		return true;	}
	return false;
}

bool InputClass::IsCPressed()
{
	if(m_keyboardState[DIK_C] & 0x80)
	{		return true;	}
	return false;
}

bool InputClass::IsVPressed()
{
	if(m_keyboardState[DIK_V] & 0x80)
	{		return true;	}
	return false;
}
bool InputClass::IsPgUpPressed()
{
	if(m_keyboardState[DIK_PGUP] & 0x80)
	{		return true;	}
	return false;
}
bool InputClass::IsPgDownPressed()
{
	if(m_keyboardState[DIK_PGDN] & 0x80)
	{		return true;	}
	return false;
}


bool InputClass::IsWPressed()
{
	if(m_keyboardState[DIK_W] & 0x80)
	{		return true;	}
	return false;
}
bool InputClass::IsSPressed()
{
	if(m_keyboardState[DIK_S] & 0x80)
	{		return true;	}
	return false;
}
bool InputClass::IsDPressed()
{
	if(m_keyboardState[DIK_D] & 0x80)
	{		return true;	}
	return false;
}
bool InputClass::IsQPressed()
{
	if(m_keyboardState[DIK_Q] & 0x80)
	{		return true;	}
	return false;
}
bool InputClass::IsEPressed()
{
	if(m_keyboardState[DIK_E] & 0x80)
	{		return true;	}
	return false;
}



bool InputClass::IsRBracketPressed()
{
	
	if(m_keyboardState[DIK_RBRACKET] & 0x80)
	{
		return true;	
	}
	return false;
}


bool InputClass::IsLBracketPressed()
{	

	if(m_keyboardState[DIK_LBRACKET] & 0x80)
	{
		
		return true;	
	}
	return false;
}



bool InputClass::WasRBracketPressed()
{
	

	if(RBracketPressed == 1)
	{
		RBracketPressed = 2;
		return true;	
	}
	return false;
}


bool InputClass::WasLBracketPressed()
{	
	if(LBracketPressed == 1)
	{
		LBracketPressed = 2;
		return true;	
	}
	return false;
}




bool InputClass::IsSpacePressed() {return false;}
bool InputClass::IsLCtrlPressed() {return false;}






void InputClass::GetMouseLocation(int& mouseX, int& mouseY)
{
	mouseX = (int)m_mouseX;
	mouseY = (int)m_mouseY;
	return;
}


void InputClass::GetMouseAcceleration(float& mouseX, float& mouseY)
{
	mouseX = v_mouseX;
	mouseY = v_mouseY;
	return;
}


void InputClass::GetKeyDown(char keyList[256])
{
	char temp;


	for (int i=0; i< 256 ;i++)
	{
		if (m_keyboardState[i]!=0)
		{
			//string str;
			//str.append(reinterpret_cast<const char*>(m_keyboardState[i]);
			temp = (char)(i+127);
			m_keyboardState[i]=0;
			keyList[i] = temp;
		}

	}

	//keyList = 'a';
//	return keyList;
}


bool InputClass::IsKeyPressed(int Key)
{
	if(m_keyboardState[Key] & 0x80)
	{
	return true;
	}

return false;
} //KeyPressed


bool InputClass::WasKeyPressed(int Key)
{
	
	if(m_keyboardStatus[Key] == 1)
	{
		m_keyboardStatus[Key] = 2;
		return true;	
	}
	return false;

} //KeyPressed