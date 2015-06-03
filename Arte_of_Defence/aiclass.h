////////////////////////////////////////////////////////////////////////////////
// Filename: aiclass.h
////////////////////////////////////////////////////////////////////////////////

#ifndef _AICLASS_H_
#define _AICLASS_H_


//////////////
// INCLUDES //
//////////////
#include <math.h>
#include <d3d11.h>
#include <d3dx10math.h>
#include "positionclass.h"
#include <string>

////////////////////////////////////////////////////////////////////////////////
// Class name: AIClass
////////////////////////////////////////////////////////////////////////////////
class AIClass
{
public:

	AIClass::AIClass();
void AIClass::Initialize();
AIClass::AIClass(const AIClass& other);
AIClass::~AIClass();




	bool IsWPressed();
	bool IsAPressed();
	bool IsSPressed();
	bool IsDPressed();
	bool IsQPressed();
	bool IsEPressed();
	void GetMouseInput(float& mx,float& my);
	void SetMouseInput(float mx,float my);
	bool Frame(float, PositionClass& me, PositionClass &you,float, float, float ,float);
	bool SetIdle();
	std::string AIClass::GetState();

	bool AIClass::SetParrying(float );	
	bool AIClass::IsParrying();
	bool AIClass::FrameActions(float);

private:
	PositionClass* m_pos;
	PositionClass* y_pos;

	bool AIClass::Strike(float ,float);
	bool AIClass::Block(float);
	bool AIClass::AdvanceAction(int& , float );

	bool W,Q,E,S,A,D;
	float m_mouseX, m_mouseY;

	int striking;
	int lunging;
	int parrying;
	int blocking;
	int step_left;
	int step_right;
	int backpedal;

};



#endif