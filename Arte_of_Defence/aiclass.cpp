#include "aiclass.h"
#include "GeometryClass.h"
#include <cstdlib>
#include "textclass.h"


AIClass::AIClass()
{
	Initialize();
}


void AIClass::Initialize()
{
	m_pos = 0;
	y_pos = 0;
	Q = false;
	W = false;
	E = false;
	A = false;
	S = false;
	D = false;

	m_mouseX = 0.0f, m_mouseY = 0.0f;
	striking = 0;
	lunging = 0;	
}







AIClass::AIClass(const AIClass& other)
{
}


AIClass::~AIClass()
{
}





bool AIClass::IsWPressed()
{
	return W;
}
	bool AIClass::IsAPressed()
{
	return A;
}
bool AIClass::IsSPressed()
{
	return S;
}
bool AIClass::IsDPressed()
{
	return D;
}
bool AIClass::IsQPressed()
{
	return Q;
}
bool AIClass::IsEPressed()
{
	return E;
}
void AIClass::GetMouseInput(float& mx,float& my)
{
	
	mx = m_mouseX,my=m_mouseY;
}

void AIClass::SetMouseInput(float mx,float my)
{
	if (mx > 0.5f)
		mx = 0.5f;
	if (my > 0.5f)
		my = 0.5f;
	if (mx < -0.5f)
		mx = -0.5f;
	if (my < -0.5f)
		my = -0.5f;

	m_mouseX = mx;
	m_mouseY = my;
}


bool AIClass::AdvanceAction(int& action, float frameTime)
{
	if (action > 0)
		action -= (int) frameTime;
	else
		action = 0;

	return true;

}

bool AIClass::SetParrying(float velocity)
{
	striking = 0;
	blocking = 0;
	parrying = (int)(4000.0f * velocity);

	if (parrying > 1000)
		parrying = 1000;

	return true;
}

bool AIClass::IsParrying()
{
	return parrying>0;
}


bool AIClass::FrameActions(float frameTime)
{
	AdvanceAction(striking, frameTime);
	AdvanceAction(lunging, frameTime);
	AdvanceAction(parrying, frameTime);
	AdvanceAction(step_left, frameTime);
	AdvanceAction(step_right, frameTime);
	AdvanceAction(backpedal,frameTime);
	AdvanceAction(blocking,frameTime);
	return true;
}


bool AIClass::Frame(float frameTime, PositionClass& me, PositionClass &you, float me_hp, float you_hp, float sw_pos_x,float sw_pos_y)
{
	
	
	float target_distance = 12.0f;
	float flee_distance =9.0f;
	float striking_distance = 7.0f;
	float out_of_position_distance = 16.0f;
	float clinch_distance = 3.0f;

	float time_ahead_distance = 0.05f * target_distance;
	float time_ahead_angle = 0.2f;
	

	m_pos = &me;
	y_pos = &you;

	
	
	

	float a = 	GeometryClass::GetYAngle(m_pos->GetPosition()+time_ahead_angle* m_pos->GetPosition_V(),y_pos->GetPosition()+time_ahead_angle*y_pos->GetPosition_V());
	float an = GeometryClass::NormalizeAngle(a,3.141592653f);
	
	float b = m_pos->GetRotation().y;
	float bn = GeometryClass::NormalizeAngle(b,3.141592653f);


	float c = bn-an;
	float cn = GeometryClass::NormalizeAngle(c,3.141592653f);



	if (cn > 0.1f)
		Q = true;
	else
		Q = false;

	
	if (cn < -0.1f)
		E = true;
	else
		E = false;


	float d = GeometryClass::Distance(m_pos->GetPosition()+time_ahead_distance*m_pos->GetPosition_V(), y_pos->GetPosition()+ time_ahead_distance*y_pos->GetPosition_V());


	W = false;
	S = false;
	A = false;
	D = false;


	if (d > target_distance && abs(cn) < 0.7f)
		W = true;



	if(lunging > 0)
	{

		if (abs(cn) < 0.7f && d > clinch_distance)
			W = true;

		if (d < clinch_distance && abs(cn) < 0.7f)
			S = true;


	}




	if (lunging == 0)
	{
		if (d < out_of_position_distance && abs(cn) > 2.0f) 
			W = true;


		if (backpedal > 0 && d < flee_distance)
			S = true;

		if (d < flee_distance && abs(cn) < 0.7f && ((float)rand())/RAND_MAX < 0.05f)
			backpedal = 200;


			



		if (d > flee_distance && d < target_distance && step_left == 0 && step_right == 0 && abs(cn) < 0.2f)
		{
			float r = ((float)rand())/RAND_MAX;

			if (r < 0.005f)
				step_left = 70;

			if (r > 0.05f && r < 0.01f)
				step_right = 70;
		}



		 if (((float)rand())/RAND_MAX < 0.05f)
		 {
			if ((d < flee_distance && cn > 1.0f) || (cn > 0.7f && d < out_of_position_distance))
				step_right = 200;
				//D = true;


			if ((d < flee_distance && cn < -1.0f) || (cn < -0.7f && d < out_of_position_distance))
				step_left = 200;
				//A = true;
		 }


		
		if (step_left)
			A = true;

		if (step_right)
			D = true;

	}

	
	if (blocking > 0)
	{
		Block(cn);
	}
	
	if (striking == 0 && blocking == 0)
	{
		if (d < striking_distance  && abs(cn) < 0.7f)
		{
			striking = 400;
			Strike(sw_pos_x,sw_pos_y);
		}
	
	
		if (striking == 0 && d< out_of_position_distance && lunging == 0)
		{
			blocking = 400;
			Block(cn);
		}
	}


	if (d <= target_distance && d> flee_distance && striking == 0 && 
		((float)rand())/RAND_MAX < 0.01 )
	{
		lunging = 1200;
		blocking = 0;

	}

	if (abs(cn) < 0.7f && d > out_of_position_distance)
	{
		lunging = 100;
	}


	return true;
}



bool AIClass::Block(float angle)
{

	if(angle > 1.57f) angle = 1.57f;
	if(angle < -1.57f) angle = -1.57f;

	m_mouseX = -1.0f * angle / 3.141f;
	m_mouseY = 0.03f;
	return true;
}

bool AIClass::Strike(float sw_pos_x,float sw_pos_y )
{

	float mx = 1.0f,my = 1.0f;

	if( sw_pos_x > 0)
		mx = -1.0f;
	if( sw_pos_y > 0)
		my = -1.0f;


	m_mouseX = mx * ((float)rand())/RAND_MAX*1.0f;
	m_mouseY = my * ((float)rand())/RAND_MAX*1.0f;
	

	return true;
}

bool AIClass::SetIdle()
{

	Q = false;
	W = false;
	E = false;
	A = false;
	S = false;
	D = false;

	//m_mouseX = 0.0f, m_mouseY = 0.0f;
	return true;
}


std::string AIClass::GetState()
{
	
	std::string myString = "";


	
	
	if (lunging > 0)
	myString += "lunge";
	if (blocking > 0)
	myString += "block";
	if (striking > 0)
	myString += "strike";
	if (parrying > 0)
	myString += "parry";
	

	myString += "  "+  TextClass::GetString(m_mouseX,3) +"  " + TextClass::GetString(m_mouseY,3) + "  ";


	myString += "  Keys  ";

	if (W)
		myString += "W";
	if(S) 
		myString += "S";
	if (D)
		myString += "D";
	if (A)
		myString += "A";
	if (Q)
		myString += "Q";
	if (E)
		myString += "E";

	
	return myString;
}