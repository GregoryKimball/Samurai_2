////////////////////////////////////////////////////////////////////////////////
// Filename: positionclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "positionclass.h"

//The class constructor initializes all the position, rotation, frame time, and speed variables to zero.
PositionClass::PositionClass()
{
Initialize();
}


void PositionClass::Initialize()
{
	
	m_position =  D3DXVECTOR3(0.0f,0.0f,0.0f);
	m_rotation =  D3DXVECTOR3(0.0f,0.0f,0.0f);

	v_position =  D3DXVECTOR3(0.0f,0.0f,0.0f);
	v_rotation =  D3DXVECTOR3(0.0f,0.0f,0.0f);
	a_position =  D3DXVECTOR3(0.0f,0.0f,0.0f);
	a_rotation =  D3DXVECTOR3(0.0f,0.0f,0.0f);



	m_frameTime = 0.0f;

	m_forwardSpeed   = 0.0f;
	m_backwardSpeed  = 0.0f;
	m_upwardSpeed    = -1.0f;
	m_downwardSpeed  = 0.0f;
	m_leftStrafeSpeed = 0.0f;
	m_rightStrafeSpeed = 0.0f;
	m_leftTurnSpeed  = 0.0f;
	m_rightTurnSpeed = 0.0f;
	m_lookUpSpeed    = 0.0f;
	m_lookDownSpeed  = 0.0f;

	m_leftRollSpeed = 0.0f;
	m_rightRollSpeed = 0.0f;

	m_midAir = true;
	m_floating = false;
}







PositionClass::PositionClass(const PositionClass& other)
{
}


PositionClass::~PositionClass()
{
}

//The SetPosition and SetRotation functions are used for setting the position and rotation of the viewer/camera. These functions are generally used to initialize the position of the camera other than at the origin. In this tutorial the camera will be set slightly back from the grid and in the center of it.

void PositionClass::SetPosition(float x, float y, float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
	return;
}


void PositionClass::SetRotation(float x, float y, float z)
{
	m_rotation.x = x;
	m_rotation.y = y;
	m_rotation.z = z;
	return;
}

//The GetPosition and GetRotation functions return the current position and rotation of the camera location. In this tutorial these functions are called to provide the location and rotation of the camera for display purposes. We will draw the position/rotation as text strings on the left side of the screen. This is very useful for debugging.

void PositionClass::GetPosition(float& x, float& y, float& z)
{
	x = m_position.x;
	y = m_position.y;
	z = m_position.z;
	return;
}

void PositionClass::GetRotation(float& x, float& y, float& z)
{
	x = m_rotation.x;
	y = m_rotation.y;
	z = m_rotation.z;
	return;
}


D3DXVECTOR3 PositionClass::GetPosition()
{
	return m_position;
}

D3DXVECTOR3 PositionClass::GetPosition_V()
{
	return v_position;
}

D3DXVECTOR3 PositionClass::GetRotation_V()
{
	return v_position;
}

D3DXVECTOR3 PositionClass::GetRotation()
{
	return m_rotation;
}

float PositionClass::GetPosX()
{	return m_position.x;}
float PositionClass::GetPosY()
{	return m_position.y;}
float PositionClass::GetPosZ()
{	return m_position.z;}


float PositionClass::GetRotX()
{	return m_rotation.x;}
float PositionClass::GetRotY()
{	return m_rotation.y;}
float PositionClass::GetRotZ()
{	return m_rotation.z;}


void PositionClass::SetRotX(float s)
{	m_rotation.x = s;}
void PositionClass::SetRotY(float s)
{	m_rotation.y = s;}
void PositionClass::SetRotZ(float s)
{	m_rotation.z = s;}

void PositionClass::SetRotation(D3DXVECTOR3 d)
{	m_rotation = d;}
void PositionClass::SetPosition(D3DXVECTOR3 d)
{	m_position = d;}
void PositionClass::SetRotation_V(D3DXVECTOR3 d)
{	v_rotation = d;}
void PositionClass::SetPosition_V(D3DXVECTOR3 d)
{	v_position = d;}

//The SetFrameTime function needs to be called each frame. It stores the current frame time inside a private member variable and is then used by the movement calculation functions. This way regardless of the speed that the application is running at the movement and rotation speed remains the same. If this wasn't done then the movement rate would speed up or down with the frame rate.

void PositionClass::SetFrameTime(float time)
{
	m_frameTime = time;
	return;
}





void PositionClass::UpdatePosition()
{
	float seconds = m_frameTime*0.001f;
	float radians;

	float drag = 1.0f;
	float force = 40.f;
	

	if ( !m_floating)
	a_position.y = m_upwardSpeed * 98.0f ;

	// fwd
	radians = m_rotation.y;	
	a_position.x += sinf(radians) * m_forwardSpeed *force ;
	a_position.z += cosf(radians) * m_forwardSpeed * force ;

	//bk
	radians = m_rotation.y;
	a_position.x -= sinf(radians)  * m_backwardSpeed*force ;
	a_position.z -= cosf(radians)  * m_backwardSpeed*force ;

	//strafe left
	radians = (m_rotation.y+90* 0.0174532925f) ;
	a_position.x -= sinf(radians) * m_leftStrafeSpeed*force ;
	a_position.z -= cosf(radians) * m_leftStrafeSpeed*force ;

	//strafe right
	radians = (m_rotation.y-90* 0.0174532925f) ;
	a_position.x -= sinf(radians) * m_rightStrafeSpeed*force ;
	a_position.z -= cosf(radians) * m_rightStrafeSpeed*force ;


	//if (abs(a_position.x) > abs(v_position.x * drag))
		
	//a_position.y -= v_position.y  * drag;
	//if (abs(a_position.z) > abs(v_position.z * drag))
	
	
	a_position.x -= v_position.x * drag;
	a_position.z -= v_position.z  * drag;

	a_rotation.x -= v_rotation.x * drag;
	a_rotation.y -= v_rotation.y * drag;
	a_rotation.z -= v_rotation.z * drag;

	a_rotation *= 0.5f;

	a_position.x *= 0.5f;
	a_position.z *= 0.5f;



	v_position += a_position * seconds;
	m_position += v_position * seconds;

	v_rotation += a_rotation * seconds;
	m_rotation += v_rotation * seconds;


	

}

void PositionClass::SetMomentum()
{
	float skates = 0.005f;
	m_rotation.x = a_position.z * skates * cosf(m_rotation.y) + a_position.x * skates * sinf(m_rotation.y);
	m_rotation.z = a_position.x * -skates * cosf(m_rotation.y) + a_position.z * skates * sinf(m_rotation.y);	

}



void PositionClass::UpdateGravity(float ground, float height)
{
	
	float seconds = m_frameTime*0.001f;

	if ((m_position.y + v_position.y * seconds) - height < ground)
	{		
		v_position.y = 0.0f;//v_position.y * -0.2f;
		m_position.y = ground + height;
		m_midAir = false;
	}
	else
	{
		m_midAir = true;
	}
}


//This function calculates the forward speed and movement of the viewer/camera.

void PositionClass::MoveForward(bool keydown)
{


	// Update the forward speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_forwardSpeed += 0.1f;
		if(m_forwardSpeed > (1.0f))
		{
			m_forwardSpeed =  1.0f;
		}

	}
	else
	{
		m_forwardSpeed -= 0.1f;
		if(m_forwardSpeed < (0.0f))
		{
			m_forwardSpeed =  0.0f;
		}

	}

	
	return;
}

//This function calculates the backward speed and movement of the viewer/camera.

void PositionClass::MoveBackward(bool keydown)
{


	// Update the backward speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_backwardSpeed += 0.1f;
		if(m_backwardSpeed > (1.0f))
		{
			m_backwardSpeed =  1.0f;
		}
	}
	else
	{
		m_backwardSpeed -= 0.1f;		
		if(m_backwardSpeed < (0.0f))
		{
			m_backwardSpeed =  0.0f;
		}
	}


	return;
}





void PositionClass::StrafeLeft(bool keydown)
{
	if(keydown)
	{
		m_leftStrafeSpeed += 0.1f;
		if(m_leftStrafeSpeed > (1.0f))
		{
			m_leftStrafeSpeed =  1.0f;
		}
	}
	else
	{
		m_leftStrafeSpeed -=  0.1f;
		if(m_leftStrafeSpeed < (0.0f))
		{
			m_leftStrafeSpeed =  0.0f;
		}
		
	}

	
	return;
}

void PositionClass::StrafeRight(bool keydown)
{
	if(keydown)
	{
		m_rightStrafeSpeed += 0.1f;
		if(m_rightStrafeSpeed > (1.0f))
		{
			m_rightStrafeSpeed =  1.0f;
		}
	}
	else
	{
		m_rightStrafeSpeed -= 0.1f;
		if(m_rightStrafeSpeed < (0.0f))
		{
			m_rightStrafeSpeed =  0.0f;
		}

	}

	
	return;
}



//This function calculates the upward speed and movement of the viewer/camera.

void PositionClass::MoveUpward(bool keydown)
{
	
	if(keydown)
	{

		if (!m_floating)
		{
			if (!m_midAir)		
			{
				v_position.y = 35.f;
			}
		}
		else
		{
			m_upwardSpeed +=  m_frameTime *0.0001f;

			if(m_upwardSpeed > (0.01f))
			{
				m_upwardSpeed =  0.01f;
			}
		}
	}
	else
	{
		if (!m_floating)
		{
			m_upwardSpeed -=  0.1f;

			if(m_upwardSpeed < -1.0f)
			{
				m_upwardSpeed = -1.0f;
			}

		}
		else
		{
			
			m_upwardSpeed -=  m_frameTime *0.0001f;

			if(m_upwardSpeed < 0.0f)
			{
				m_upwardSpeed = 0.00f;
			}
		}
	}

	// Update the height position.
	if ( m_floating)
	m_position.y +=  m_frameTime * m_upwardSpeed;


	return;
}

//This function calculates the downward speed and movement of the viewer/camera. 

void PositionClass::MoveDownward(bool keydown)
{
	// Update the downward speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_downwardSpeed +=  m_frameTime *0.0001f;

		if(m_downwardSpeed > ( 0.01f))
		{
			m_downwardSpeed =  0.01f;
		}
	}
	else
	{
		m_downwardSpeed -=  m_frameTime *0.00007f;

		if(m_downwardSpeed < 0.0f)
		{
			m_downwardSpeed = 0.0f;
		}
	}

	// Update the height position.
	m_position.y -=  m_frameTime * m_downwardSpeed;

	return;
}











//This function calculates the left turn speed and rotation of the viewer/camera.

void PositionClass::TurnLeft(bool keydown)
{

	

	// Update the left turn speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_leftTurnSpeed += m_frameTime * 0.0002f * 0.0174532925f;

		if(m_leftTurnSpeed > ( 0.12f * 0.0174532925f))
		{
			m_leftTurnSpeed =  0.12f * 0.0174532925f;
		}
	}
	else
	{
		m_leftTurnSpeed -=  m_frameTime *0.00015f* 0.0174532925f;

		if(m_leftTurnSpeed < 0.0f)
		{
			m_leftTurnSpeed = 0.0f;
		}
	}

	// Update the rotation.
	m_rotation.y -= m_frameTime * m_leftTurnSpeed ;

	// Keep the rotation in the 0 to 2pi range.
	if(m_rotation.y < 0.0f)
	{
		m_rotation.y += 6.283185306f;
	}

	return;
}

//This function calculates the right turn speed and rotation of the viewer/camera.

void PositionClass::TurnRight(bool keydown)
{
	// Update the right turn speed movement based on the frame time and whether the user is holding the key down or not.

	
	if(keydown)
	{
		m_rightTurnSpeed +=  m_frameTime *0.0002f * 0.0174532925f;

		if(m_rightTurnSpeed > ( 0.12f * 0.0174532925f))
		{
			m_rightTurnSpeed =  0.12f * 0.0174532925f;
		}
	}
	else
	{
		m_rightTurnSpeed -=  m_frameTime *0.00015f * 0.0174532925f;

		if(m_rightTurnSpeed < 0.0f)
		{
			m_rightTurnSpeed = 0.0f;
		}
	}

	// Update the rotation.
	m_rotation.y += m_frameTime * m_rightTurnSpeed;

	// Keep the rotation in the 0 to 2pi range.
	if(m_rotation.y > 6.283185306f)
	{
		m_rotation.y -= 6.283185306f;
	}

	return;
}

//This function calculates the upward turn speed and rotation of the viewer/camera.

void PositionClass::LookUpward(bool keydown)
{
	// Update the upward rotation speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_lookUpSpeed += m_frameTime * 0.01f * 0.0174532925f;

		if(m_lookUpSpeed > ( 0.05f * 0.0174532925f))
		{
			m_lookUpSpeed =  0.05f * 0.0174532925f;
		}
	}
	else
	{
		m_lookUpSpeed -=  m_frameTime *0.005f * 0.0174532925f;

		if(m_lookUpSpeed < 0.0f)
		{
			m_lookUpSpeed = 0.0f;
		}
	}

	// Update the rotation.
	m_rotation.x -= m_frameTime*m_lookUpSpeed;

	// Keep the rotation maximum 90 degrees.
	
	
	//if(m_rotation.x > 1.5707963265f)
//			m_rotation.x = 1.5707963265f;
	if(m_rotation.x > 3.1415926f)
			{
				m_rotation.x -= 6.283185306f;
			}
	if(m_rotation.x < -3.1415926f)
			{
				m_rotation.x += 6.283185306f;
			}
	

	return;
}

//This function calculates the downward turn speed and rotation of the viewer/camera.

void PositionClass::LookDownward(bool keydown)
{
	// Update the downward rotation speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_lookDownSpeed += m_frameTime *0.01f * 0.0174532925f;

		if(m_lookDownSpeed > ( 0.05f * 0.0174532925f))
		{
			m_lookDownSpeed =  0.05f * 0.0174532925f;
		}
	}
	else
	{
		m_lookDownSpeed -=  m_frameTime *0.005f * 0.0174532925f;

		if(m_lookDownSpeed < 0.0f)
		{
			m_lookDownSpeed = 0.0f;
		}
	}

	// Update the rotation.
	m_rotation.x += m_frameTime*m_lookDownSpeed;

	// Keep the rotation maximum 90 degrees.
	//if(m_rotation.x < -1.5707963265f)
	//{		m_rotation.x = -1.5707963265f;	}


	/*if(m_rotation.x < 0.0f)
	{
		m_rotation.x += 6.283185306f;
	}*/

		if(m_rotation.x > 3.1415926f)
			{
				m_rotation.x -= 6.283185306f;
			}
	if(m_rotation.x < -3.1415926f)
			{
				m_rotation.x += 6.283185306f;
			}
	
		
	return;
}





void PositionClass::RollLeft(bool keydown)
{

	

	// Update the left turn speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_leftRollSpeed += m_frameTime * 0.0002f * 0.0174532925f;

		if(m_leftRollSpeed > ( 0.08f * 0.0174532925f))
		{
			m_leftRollSpeed =  0.08f * 0.0174532925f;
		}
	}
	else
	{
		m_leftRollSpeed -=  m_frameTime *0.00015f * 0.0174532925f;

		if(m_leftRollSpeed < 0.0f)
		{
			m_leftRollSpeed = 0.0f;
		}
	}

	// Update the rotation.
	m_rotation.z += m_frameTime * m_leftRollSpeed ;

	// Keep the rotation in the 0 to 360 range.
	if(m_rotation.z < 0.0f)
	{
		m_rotation.z += 6.283185306f;
	}

	return;
}



void PositionClass::RollRight(bool keydown)
{

	

	// Update the left turn speed movement based on the frame time and whether the user is holding the key down or not.
	if(keydown)
	{
		m_rightRollSpeed += m_frameTime * 0.0002f * 0.0174532925f;

		if(m_rightRollSpeed > ( 0.08f * 0.0174532925f))
		{
			m_rightRollSpeed =  0.08f * 0.0174532925f;
		}
	}
	else
	{
		m_rightRollSpeed -=  m_frameTime *0.00015f * 0.0174532925f;

		if(m_rightRollSpeed < 0.0f)
		{
			m_rightRollSpeed = 0.0f;
		}
	}

	// Update the rotation.
	m_rotation.z -= m_frameTime * m_rightRollSpeed ;

	// Keep the rotation in the 0 to 360 range.
	if(m_rotation.z > 6.283185306f)
	{
		m_rotation.z -= 6.283185306f;
	}

	return;
}