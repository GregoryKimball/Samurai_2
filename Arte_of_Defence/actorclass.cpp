#include "actorclass.h"



ActorClass::ActorClass()
{

}

ActorClass::ActorClass(const ActorClass& other)
{
}



ActorClass::~ActorClass()
{
}




bool ActorClass::Initialize()
{

	limbs = new LimbClass[LIMB_COUNT];
	active = false;
	m_position.Initialize();

	strength = 1.0f;
	dexterity = 1.0f;
	sword_setpoint_X = 0.0f;
	sword_setpoint_Y = 0.0f;
	sword_position_X = 0.0f;
	sword_position_Y = 0.0f;
	sword_velocity_X = 0.0f;
	sword_velocity_Y = 0.0f;
	sword_acc_X= 0.0f;
	sword_acc_Y= 0.0f;

	team = 0;		
	m_AI.Initialize();

	return true;
}



void ActorClass::ResetLimbs()
{
	
	for(int i =0; i<LIMB_COUNT; i++)
	{
		limbs[i].attached = true;
		limbs[i].limbType = static_cast<LimbTypeEnum>(i);
		limbs[i].limbAngle = D3DXVECTOR3(0.0f, 3.141592653f, 0.0f);
		limbs[i].Hitpoints = 100.0f;


			//set 2 end -> 4
			//set 3 end -> 5
		//set 6-> 8
		//set 7 - 9


		switch (i) 
		{
			case 0://head
				limbs[i].limbBegin = D3DXVECTOR3(0.0f, 0.8f, -0.1f);						
				limbs[i].limbAngle = D3DXVECTOR3(-1.67079632f, 0.0f, 3.14159f);
				limbs[i].limbLength = 1.05f;
				limbs[i].limbWidth = 0.4f;
				limbs[i].Hitpoints = 100.0f;
				break;
			case 1://torso
				limbs[i].limbBegin = D3DXVECTOR3(0.0f, 1.0f, 0.0f);				
				limbs[i].limbAngle = D3DXVECTOR3(1.67079632f, 0.0f, 3.14159f);
				limbs[i].limbLength = 1.9f;
				limbs[i].limbWidth = 0.65f;
				limbs[i].Hitpoints = 300.0f;
				break;		 
				
			case 2:// l arm
				limbs[i].limbBegin = D3DXVECTOR3(-0.8f, 0.4f, 0.0f);				
				limbs[i].limbAngle = D3DXVECTOR3(0.0f, 0.0f, 1.57f);//3.141f
				limbs[i].limbLength = 1.1f;
				limbs[i].limbWidth = 0.2f;
				limbs[i].Hitpoints = 100.0f;
				break;		 
			case 3:// r arm
				limbs[i].limbBegin = D3DXVECTOR3(0.8f, 0.4f, 0.0f);
				limbs[i].limbAngle = D3DXVECTOR3(0.0f, 0.0f, 3.141f);
				limbs[i].limbLength = 1.1f;
				limbs[i].limbWidth = 0.2f;
				limbs[i].Hitpoints = 100.0f;
				break;		 
			case 4:// l hand
				limbs[i].limbBegin = D3DXVECTOR3(-1.0f, -0.9f, 0.0f);		
				limbs[i].limbAngle = D3DXVECTOR3(0.0f, 0.0f, 3.141f);
				limbs[i].limbLength = 1.3f;
				limbs[i].limbWidth = 0.2f;
				limbs[i].Hitpoints = 100.0f;
				break;		 
			case 5:// r hand
				limbs[i].limbBegin = D3DXVECTOR3(1.0f, -0.9f, 0.0f);		
				limbs[i].limbAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				limbs[i].limbLength = 1.3f;
				limbs[i].limbWidth = 0.2f;
				limbs[i].Hitpoints = 100.0f;
				break;		 
			case 6:// l leg
				limbs[i].limbBegin = D3DXVECTOR3(-0.3f, -1.2f, 0.0f);				
				//limbs[i].limbAngle = D3DXVECTOR3(0.0f, -1.57079632f, 0.0f);
				limbs[i].limbAngle = D3DXVECTOR3(1.37f, -1.57f, +3.14159f);				
				limbs[i].limbLength = 2.0f;
				limbs[i].limbWidth = 0.3f;
				limbs[i].Hitpoints = 100.0f;
				break;		 
			case 7:// r leg 
				limbs[i].limbBegin = D3DXVECTOR3(0.3f, -1.2f, 0.0f);		
				//limbs[i].limbAngle = D3DXVECTOR3(0.0f, 1.57079632f, 0.0f);
				limbs[i].limbAngle = D3DXVECTOR3(1.37f, 1.57f, -3.141459f);
				limbs[i].limbLength = 2.0f;
				limbs[i].limbWidth = 0.3f;
				limbs[i].Hitpoints = 100.0f;
				break;		 
			case 8: // l foot
				limbs[i].limbBegin = D3DXVECTOR3(-0.6f, -3.0f, 0.0f);				
				//limbs[i].limbAngle = D3DXVECTOR3(1.0f, -0.0f, 3.14159f);
				limbs[i].limbAngle = D3DXVECTOR3(1.970796327f, -0.0f, 3.14159f);
				limbs[i].limbLength = 2.0f;
				limbs[i].limbWidth = 0.2f;
				limbs[i].Hitpoints = 100.0f;
				break;		 
			case 9:// r foot
				limbs[i].limbBegin = D3DXVECTOR3(0.6f, -3.0f, 0.0f);		
				//limbs[i].limbAngle = D3DXVECTOR3(1.0f, +3.14159f, 3.14159f);
				limbs[i].limbAngle = D3DXVECTOR3(1.970796327f, +0.0f, 3.14159f);
				limbs[i].limbLength = 2.0f;
				limbs[i].limbWidth = 0.2f;
				limbs[i].Hitpoints = 100.0f;
				break;		 

			case 10:// sword
				limbs[i].limbBegin = D3DXVECTOR3(0.0f, -0.0f, 1.0f);				
				limbs[i].limbAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				limbs[i].limbLength = 3.7f;
				limbs[i].limbWidth = 0.4f;
				break;	//*/
			
		}

		limbs[i].HitpointsMax = limbs[i].Hitpoints;

	}

}


LimbClass* ActorClass::KillActor(float sx,float sy)
{

	active = false;

	/*for(int i = 0;i<LIMB_COUNT;i++)
	{
		limbs[i].attached = false;
	}*/		

	return limbs;
}



bool ActorClass::IsDead()
{


	if (!limbs[0].attached )
		return true;

	if (!limbs[1].attached )
		return true;

	if ((!limbs[6].attached ||!limbs[8].attached) && (!limbs[7].attached||!limbs[9].attached))
		return true;

	if ((!limbs[2].attached ||!limbs[4].attached) && (!limbs[3].attached||!limbs[5].attached))
		return true;

	return false;
}

bool ActorClass::Heal()
{
	for(int i=0;i<LIMB_COUNT;i++)
	{
		limbs[i].Hitpoints = limbs[i].HitpointsMax;
	}
	return true;
}


void ActorClass::UpdateSword( float mx, float my)
{
	sword_setpoint_X = mx;
	sword_setpoint_Y = my;

	float drag = 0.06f;
	float dx = (sword_setpoint_X - sword_position_X);
	float dy = (sword_setpoint_Y - sword_position_Y);


	if(m_AI.IsParrying())
	{
		dx = 0.0f;
		dy = 0.0f;
	}




	sword_acc_X = dx * 0.01f;
	sword_acc_Y = dy * 0.01f;
		
	sword_acc_X -= sword_velocity_X*drag;
	sword_acc_Y -= sword_velocity_Y*drag;



	sword_velocity_X += sword_acc_X;//*dx;
	sword_velocity_Y += sword_acc_Y;//*dy;

	sword_position_X += sword_velocity_X;
	sword_position_Y += sword_velocity_Y;

	
	float motionLimit = 0.5f;

	if (m_AI.IsParrying())
	{
		motionLimit  = 1.8f;
		if(sword_position_X > motionLimit)
		{
			sword_position_X = motionLimit;			
		}
		if(sword_position_X < -1.0f*motionLimit)
		{
			sword_position_X = -1.0f*motionLimit;			
		}
		if(sword_position_Y > motionLimit)
		{
			sword_position_Y = motionLimit;			
		}
		if(sword_position_Y < -1.0f*motionLimit)
		{
			sword_position_Y = -1.0f*motionLimit;		
		}
	}
	else
	{
		motionLimit = 0.5f;

		if(sword_position_X > motionLimit)
		{
			sword_position_X = motionLimit;
			sword_velocity_X = 0.0f;
			sword_velocity_Y = 0.0f;
		}
		if(sword_position_X < -1.0f*motionLimit)
		{
			sword_position_X = -1.0f*motionLimit;
			sword_velocity_X = 0.0f;
			sword_velocity_Y = 0.0f;
		}
		if(sword_position_Y > motionLimit)
		{
			sword_position_Y = motionLimit;
			sword_velocity_X = 0.0f;
			sword_velocity_Y = 0.0f;
		}
		if(sword_position_Y < -1.0f*motionLimit)
		{
			sword_position_Y = -1.0f*motionLimit;
			sword_velocity_X = 0.0f;
			sword_velocity_Y = 0.0f;
		}
	}

	
	
	//sword position ranges from 0.5 to -0.5
	
	//SETTING the LIMBS




	float distance = 2.2f;

	limbs[10].limbAngle.x = sword_position_Y * 2.0f * 1.00f;
	limbs[10].limbAngle.y =  sword_position_X * 2.0f * 1.3f;
	limbs[10].limbAngle.z = (float) (1);

	limbs[10].limbBegin = GeometryClass::GetEnd(D3DXVECTOR3(0.0f,0.0f,0.0f),limbs[10].limbAngle, distance);
	



	limbs[2].limbAngle = GeometryClass::GetAngle(limbs[2].limbBegin,limbs[10].limbBegin,m_position.GetRotation(),D3DXVECTOR3(0.0f,0.0f,0.0f));
	limbs[3].limbAngle = GeometryClass::GetAngle(limbs[3].limbBegin,limbs[10].limbBegin,m_position.GetRotation(),D3DXVECTOR3(0.0f,0.0f,0.0f));

	limbs[2].limbAngle.x += 0.4f;
	limbs[2].limbAngle.y += sword_position_X;

	limbs[3].limbAngle.x +=  0.4f;
	limbs[3].limbAngle.y += sword_position_X;	



	limbs[4].limbBegin = GeometryClass::GetEnd(limbs[2].limbBegin,limbs[2].limbAngle, limbs[2].limbLength);	
	limbs[5].limbBegin = GeometryClass::GetEnd(limbs[3].limbBegin,limbs[3].limbAngle, limbs[3].limbLength);	
	//limbs[4].limbAngle.x = sword_position_Y * 2.0f * 1.00f - 0.0f;
	//limbs[4].limbAngle.y = sword_position_X * 2.0f * 1.57f + 1.4f;
	//limbs[5].limbAngle.x = sword_position_Y * 2.0f * 1.00f - 0.0f;
	//limbs[5].limbAngle.y = sword_position_X * 2.0f * 1.57f - 1.4f;
	
	


	//limbs[4].limbBegin = GeometryClass::GetEnd(limbs[10].limbBegin,limbs[2].limbAngle, -1.0f* limbs[2].limbLength);	
	//limbs[5].limbBegin = GeometryClass::GetEnd(limbs[10].limbBegin,limbs[3].limbAngle, -1.0f * limbs[3].limbLength);	

	limbs[4].limbAngle = GeometryClass::GetAngle(limbs[4].limbBegin,limbs[10].limbBegin,m_position.GetRotation(),D3DXVECTOR3(0.0f,0.0f,0.0f));
	limbs[5].limbAngle = GeometryClass::GetAngle(limbs[5].limbBegin,limbs[10].limbBegin,m_position.GetRotation(),D3DXVECTOR3(0.0f,0.0f,0.0f));
	
	/*
	//l arm
	limbs[2].limbAngle.x = (float) ((sword_position_Y)* 3.14/2 + 0.4f);
	limbs[2].limbAngle.y = (float) ((sword_position_X)* 3.14);

	limbs[4].limbBegin = GeometryClass::GetEnd(limbs[2].limbBegin,limbs[2].limbAngle, limbs[2].limbLength);	
	limbs[4].limbAngle.x = limbs[2].limbAngle.x - 0.8f;
	limbs[4].limbAngle.y = limbs[2].limbAngle.y + 0.4f;

	//r arm
	limbs[3].limbAngle.x = (float) ((sword_position_Y)* 3.14/2 + 0.4f);
	limbs[3].limbAngle.y = (float) ((sword_position_X)* 3.14);	

	limbs[5].limbBegin = GeometryClass::GetEnd(limbs[3].limbBegin,limbs[3].limbAngle, limbs[3].limbLength);	
	limbs[5].limbAngle.x = limbs[3].limbAngle.x - 0.8f;
	limbs[5].limbAngle.y = limbs[3].limbAngle.y - 0.4f;
	
	limbs[10].limbBegin = GeometryClass::GetEnd(limbs[5].limbBegin,limbs[5].limbAngle, limbs[5].limbLength);
	limbs[10].limbAngle.x = (float) ((sword_position_Y) * 1);
	limbs[10].limbAngle.y = (float) ((sword_position_X)*  1);
	limbs[10].limbAngle.z = (float) (1);	
	*/

	
	


	




}


void ActorClass::SyncModelToActor(int limb_index, D3DXVECTOR3& begin, D3DXVECTOR3& angle)
{			
			
	D3DXMATRIX rotationMatrix;
	D3DXVECTOR3 lookAt;
	D3DXVECTOR3 lookAt2;
	D3DXVECTOR3 l_angle, l_start, l_end;
	D3DXVECTOR3 r;

	int j = limb_index;

			

	r = m_position.GetRotation();
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, r.y, r.x, r.z);


	lookAt = limbs[j].limbBegin;
	lookAt2 = GeometryClass::GetEnd(limbs[j].limbBegin,limbs[j].limbAngle,limbs[j].limbLength);
	D3DXVECTOR3 l = limbs[j].limbAngle;


	D3DXVec3TransformCoord(&lookAt, &lookAt, &rotationMatrix);
	l_start =m_position.GetPosition() + lookAt;
				
	D3DXVec3TransformCoord(&lookAt2, &lookAt2, &rotationMatrix);
	l_end = m_position.GetPosition() + lookAt2;


				
	if (j==0)
		j= 0;

	l_angle = GeometryClass::GetAngle(l_start, l_end, r,l);




	begin = l_start;
	angle = l_angle;




	


	/*
	if (actor_index == 0)
	{
		float deg = 57.29577951f;
		TextClass::debug_strings[0] = "Actor facing:        " + TextClass::GetString(r*deg,2);

		//TextClass::debug_strings[j+1] = "Limb " + TextClass::GetString(j) + " :           " + TextClass::GetString(l_angle,2);
		if ( j==0)
		{
			TextClass::debug_strings[1] = "Head anim  " + TextClass::GetString(j) + " :           " + TextClass::GetString(m_actors[i].limbs[j].limbAngle*deg,2);
			TextClass::debug_strings[2] = "Head displ " + TextClass::GetString(j) + " :           " + TextClass::GetString(l_end - l_start,3);
			TextClass::debug_strings[3] = "Head angle " + TextClass::GetString(j) + " :           " + TextClass::GetString(l_angle*deg,2);
			
		}
		if ( j==1)
		{
			TextClass::debug_strings[4] = "Tors anim  " + TextClass::GetString(j) + " :           " + TextClass::GetString(m_actors[i].limbs[j].limbAngle*deg,2);
			TextClass::debug_strings[5] = "Tors displ " + TextClass::GetString(j) + " :           " + TextClass::GetString(l_end - l_start,3);
			TextClass::debug_strings[6] = "Tors angle " + TextClass::GetString(j) + " :           " + TextClass::GetString(l_angle*deg,2);
			
		}

		if ( j==4)
		{
			TextClass::debug_strings[8] = "lh anim  " + TextClass::GetString(j) + " :           " + TextClass::GetString(m_actors[i].limbs[j].limbAngle*deg,2);
			TextClass::debug_strings[9] = "lh displ " + TextClass::GetString(j) + " :           " + TextClass::GetString(l_end - l_start,3);
			TextClass::debug_strings[10] = "lh angle " + TextClass::GetString(j) + " :           " + TextClass::GetString(l_angle*deg,2);
			
		}
		if ( j==5)
		{
			TextClass::debug_strings[11] = "rh anim  " + TextClass::GetString(j) + " :           " + TextClass::GetString(m_actors[i].limbs[j].limbAngle*deg,2);
			TextClass::debug_strings[12] = "rh displ " + TextClass::GetString(j) + " :           " + TextClass::GetString(l_end - l_start,3);
			TextClass::debug_strings[13] = "rh angle " + TextClass::GetString(j) + " :           " + TextClass::GetString(l_angle*deg,2);
			
		}


		if ( j==9)
		{
			TextClass::debug_strings[14] = "c0p  " + TextClass::GetString(j) + " :           " + TextClass::GetString(m_corpses[0].m_position.GetPosition(),2);
			TextClass::debug_strings[15] = "c0r " + TextClass::GetString(j) + " :           " + TextClass::GetString(m_corpses[0].m_position.GetRotation()*deg,2);
			
		}
	}
	*/
		
			
}