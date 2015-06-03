////////////////////////////////////////////////////////////////////////////////
// Filename: positionclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _POSITIONCLASS_H_
#define _POSITIONCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <math.h>
#include <d3d11.h>
#include <d3dx10math.h>

////////////////////////////////////////////////////////////////////////////////
// Class name: PositionClass
////////////////////////////////////////////////////////////////////////////////
class PositionClass
{
public:
	PositionClass();
	PositionClass(const PositionClass&);
	~PositionClass();

	void PositionClass::Initialize();

//The PositionClass has some helper functions to set and retrieve the position and rotation of the viewer/camera.

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);

	void GetPosition(float&, float&, float&);
	void GetRotation(float&, float&, float&);

	void SetPosition(D3DXVECTOR3);
	void SetRotation(D3DXVECTOR3);
	void SetPosition_V(D3DXVECTOR3);
	void SetRotation_V(D3DXVECTOR3);
	void PositionClass::SetMomentum();

	D3DXVECTOR3 GetPosition();
	D3DXVECTOR3 GetRotation();
	D3DXVECTOR3 GetPosition_V();
	D3DXVECTOR3 GetRotation_V();



	float GetPosX();
	float GetPosY();
	float GetPosZ();


	float GetRotX();
	float GetRotY();
	float GetRotZ();

	void SetRotX(float);
	void SetRotY(float);
	void SetRotZ(float);

//SetFrameTime is used to keep the viewer/camera in sync with the speed of the application.

	void SetFrameTime(float);
	void UpdatePosition();
	void UpdateGravity(float,float);


//The movement functions are called to move the viewer/camera based on the user input.

	void MoveForward(bool);
	void MoveBackward(bool);
	void MoveUpward(bool);
	void MoveDownward(bool);
	void TurnLeft(bool);
	void TurnRight(bool);
	void StrafeLeft(bool);
	void StrafeRight(bool);
	void LookUpward(bool);
	void LookDownward(bool);
	void RollLeft(bool);
	void RollRight(bool);
	bool m_floating;

private:

	D3DXVECTOR3 m_position, m_rotation;
	D3DXVECTOR3 v_position, v_rotation;
	D3DXVECTOR3 a_position, a_rotation;


	//float m_positionX, m_positionY, m_positionZ;
	//float m_rotationX, m_rotationY, m_rotationZ;

	float m_frameTime;

	float m_forwardSpeed, m_backwardSpeed;
	float m_upwardSpeed, m_downwardSpeed;
	float m_leftTurnSpeed, m_rightTurnSpeed;
	float m_lookUpSpeed, m_lookDownSpeed;
	float m_leftStrafeSpeed, m_rightStrafeSpeed;
	float m_leftRollSpeed,m_rightRollSpeed;

	bool m_midAir;
	
};

#endif
