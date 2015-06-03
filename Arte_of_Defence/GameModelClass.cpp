

#include "gamemodelclass.h"


GameModelClass::GameModelClass()
{

}

GameModelClass::GameModelClass(const GameModelClass& other)
{
}



GameModelClass::~GameModelClass()
{
}




bool GameModelClass::Initialize()
{

	m_actors = new ActorClass[ACTOR_COUNT];



	for(int i =0; i<ACTOR_COUNT; i++)
	{

		m_actors[i].Initialize();
		/*
		m_actors[i].limbs = new LimbStruct[LIMB_COUNT];
		m_actors[i].active = false;
		m_actors[i].m_position.Initialize();


		m_actors[i].strength = 1.0f;
		m_actors[i].dexterity = 1.0f;
		m_actors[i].sword_setpoint_X = 0.0f;
		m_actors[i].sword_setpoint_Y = 0.0f;
		m_actors[i].sword_position_X = 0.0f;
		m_actors[i].sword_position_Y = 0.0f;
		m_actors[i].sword_velocity_X = 0.0f;
		m_actors[i].sword_velocity_Y = 0.0f;
		m_actors[i].sword_acc_X= 0.0f;
		m_actors[i].sword_acc_Y= 0.0f;

		m_actors[i].team = 0;		
		m_actors[i].m_AI.Initialize();*/
		
	}



	Corpse_Index = 0;
	m_corpses = new CorpseStruct[CORPSE_COUNT];
	for(int i =0; i<CORPSE_COUNT; i++)
	{
		m_corpses[i].active = false;
		m_corpses[i].m_position.Initialize();
	}

	return true;
}






int GameModelClass::AddActor()
{

	int actor_index = -1;
	
	
	for(int i =0; i<ACTOR_COUNT; i++)
	{
		if (!m_actors[i].active && actor_index == -1)
		{
			actor_index = i;
			break;
		}
	}


	if (actor_index == -1)
		return actor_index;




	m_actors[actor_index].active = true;

	m_actors[actor_index].m_position.SetPosition((((float)rand()-(float)rand())/RAND_MAX) * 10.0f + 50.0f		, 
		(((float)rand()-(float)rand())/RAND_MAX) * 10.0f + 10.0f		, 
		((((float)rand()-(float)rand())/RAND_MAX) * 10.0f) + 50.0f		);

	m_actors[actor_index].m_position.SetRotation(0.0f,0.0f,1.0f);

	m_actors[actor_index].sword_setpoint_X = 0.0f;
	m_actors[actor_index].sword_setpoint_Y = 0.0f;
	m_actors[actor_index].sword_position_X = 0.0f;
	m_actors[actor_index].sword_position_Y = 0.0f;
	m_actors[actor_index].sword_velocity_X = 0.0f;
	m_actors[actor_index].sword_velocity_Y = 0.0f;
	m_actors[actor_index].sword_acc_X= 0.0f;
	m_actors[actor_index].sword_acc_Y= 0.0f;		

	ResetLimbs(actor_index);
	

	return actor_index;
}


bool GameModelClass::IsValidActor(int actor_index)
{
	if (actor_index < 0) 
		return false;
	if (actor_index >= ACTOR_COUNT)
		return false; 
	if (!m_actors[actor_index].active)
		return false;

	return true;
}


int GameModelClass::AddCorpse(CorpseStruct* c)
{
	


	int corpse_index = -1;	
	
	for(int i =0; i<CORPSE_COUNT; i++)
	{
		if (!m_corpses[i].active && corpse_index == -1)
		{
			corpse_index = i;
			break;
		}
	}



	if (corpse_index == -1)
	{
		corpse_index = Corpse_Index;
		Corpse_Index ++;
		if (Corpse_Index == CORPSE_COUNT)
			Corpse_Index = 0;
	}
		//return corpse_index;

	m_corpses[corpse_index] = *c;
	

	return corpse_index;


}


void GameModelClass::KillActor(int actor_index, float sx, float sy)
{

	if (!IsValidActor(actor_index))
		return;
	
	int i = actor_index;
	LimbClass* limbs;


	limbs = m_actors[i].KillActor(sx,sy);

		

	for(int j=0;j<LIMB_COUNT;j++)
	{
		if (limbs[j].attached)
		{
			CorpseStruct * c = new CorpseStruct;
			PrepareCorpse(m_actors[i], limbs[j], sx, sy, c);
			AddCorpse(c);
		}
	}

	m_actors[i].active = false;

}


void GameModelClass::HealActor(int actor_index)
{		
	if (!IsValidActor(actor_index))
		return;

	m_actors[actor_index].Heal();	
}

void GameModelClass::HealAllActors()
{
	for(int i =0;i<ACTOR_COUNT ;i++)
	{
		HealActor(i);
	}

}

void GameModelClass::KillAllActors()
{
	for(int i =0;i<ACTOR_COUNT; i++)
	{
		if (m_actors[i].active)
		{
			if (!m_actors[i].IsDead())
				KillActor(i,0.0f,0.0f);
		}
	}
}



bool GameModelClass::IsDeadActor(int actor_index)
{
	return m_actors[actor_index].IsDead();
}

void GameModelClass::PrepareCorpse(ActorClass& actor, LimbClass& limb, float sx, float sy,CorpseStruct* corpse)
{

	limb.attached = false;

	PositionClass* p = new PositionClass;
	p->Initialize();
	p->SetPosition(actor.m_position.GetPosition() + limb.limbBegin);
						
	D3DXVECTOR3 velocity;

	velocity.x = sx*2.0f * (float)(rand() % 100 - 50);
	velocity.y = 35.0f;
	velocity.z = sy*2.0f * (float)(rand() % 100 - 50);
	p->SetPosition_V(velocity);

	velocity.x = sx*2.0f * (float)(rand() % 100 - 50);
	velocity.y = sy*2.0f * (float)(rand() % 100 - 50);
	velocity.z = 30.0f;						
	p->SetRotation_V(velocity);


	corpse->active = true;
	corpse->m_position = *p;
	corpse->limb =limb;
	corpse->team = actor.team;
}



void GameModelClass::LinkLimbToModel(int model_index,int actor_index, int limb_index)
{
	m_actors[actor_index].limbs[limb_index].model_index = model_index;
}

void GameModelClass::ResetLimbs(int actor_index)
{
	if (IsValidActor(actor_index))
		m_actors[actor_index].ResetLimbs();

}






void GameModelClass::UpdateSword(int actor_index, float mx, float my)
{
	if (IsValidActor(actor_index))
		m_actors[actor_index].UpdateSword(mx,my);
}


D3DXVECTOR3  GameModelClass::GetColorFromHitpoints(float hp, float hpmax, int team)
{
	D3DXVECTOR3 color;

	color.x = 1.0f;
	color.y = (float)(hp/hpmax);
	color.z = (float)(hp/hpmax);

	float d = (hp/hpmax);
	float d1,d2;
	if (d > 0.5f)
	{
		d1 = (d - 0.5f)/ 0.5f;
		d2 = 1.0f;
	}
	else
	{
		d1 = 0.0f;
		d2 = (d)/0.5f;
	}

	if (team == 1)
	{
		color.x = 1.0f;
		color.y = (float)(hp/hpmax);
		color.z = (float)(hp/hpmax);
	}

	if (team == 0)
	{
		color.x = (float)((100.0 - hp)/hpmax);
		color.y = (float)(hp/hpmax);
		color.z = (float)(hp/hpmax);
	}




	return color;
}


void GameModelClass::SyncModelToActor(int actor_index, int model_index, D3DXVECTOR3& begin, D3DXVECTOR3& angle, D3DXVECTOR3& color)
{
	
}




void GameModelClass::CheckCollisions()
{

	D3DXVECTOR3 sword_begin, sword_end;
	D3DXVECTOR3 limb_begin, limb_end;
	float sword_speed;
	D3DXMATRIX rotationMatrix;


	for(int i =0;i<ACTOR_COUNT;i++)
	{
		if (!m_actors[i].active)
			continue;

	}


	for(int i =0;i<ACTOR_COUNT;i++)
	{
		if (!m_actors[i].active)
			continue;




		D3DXMatrixRotationYawPitchRoll(&rotationMatrix, m_actors[i].m_position.GetRotY(), m_actors[i].m_position.GetRotX(), m_actors[i].m_position.GetRotZ());

		sword_begin = m_actors[i].limbs[10].limbBegin;
		D3DXVec3TransformCoord(&sword_begin, &sword_begin, &rotationMatrix);
		sword_begin += m_actors[i].m_position.GetPosition();

		
		sword_end = GeometryClass::GetEnd(m_actors[i].limbs[10].limbBegin,m_actors[i].limbs[10].limbAngle,m_actors[i].limbs[10].limbLength);
		D3DXVec3TransformCoord(&sword_end, &sword_end, &rotationMatrix);
		sword_end  += m_actors[i].m_position.GetPosition();


		sword_speed = sqrt(m_actors[i].sword_velocity_X * m_actors[i].sword_velocity_X + m_actors[i].sword_velocity_Y * m_actors[i].sword_velocity_Y);

		for(int j =0;j<ACTOR_COUNT;j++)
		{
			if (!m_actors[j].active || i==j || GeometryClass::Distance(m_actors[i].m_position.GetPosition(), m_actors[j].m_position.GetPosition()) > 20.0f)
				continue;
			
			D3DXMatrixRotationYawPitchRoll(&rotationMatrix, m_actors[j].m_position.GetRotY(), m_actors[j].m_position.GetRotX(), m_actors[j].m_position.GetRotZ());


			for(int k =0;k<LIMB_COUNT;k++)
			{
				if(!m_actors[j].limbs[k].attached)
					continue;

				limb_begin = m_actors[j].limbs[k].limbBegin;
				D3DXVec3TransformCoord(&limb_begin, &limb_begin, &rotationMatrix);
				limb_begin  += m_actors[j].m_position.GetPosition();

				limb_end = GeometryClass::GetEnd(m_actors[j].limbs[k].limbBegin,m_actors[j].limbs[k].limbAngle,m_actors[j].limbs[k].limbLength);
				D3DXVec3TransformCoord(&limb_end, &limb_end, &rotationMatrix);
				limb_end  += m_actors[j].m_position.GetPosition();

				//float d = GeometryClass::ClosestDistance(sword_begin, sword_end, limb_begin, limb_end) ;

				if (GeometryClass::ClosestDistance(sword_begin, sword_end, limb_begin, limb_end) < m_actors[j].limbs[k].limbWidth)
				{

					if (m_actors[j].limbs[k].limbType == SWORD)
					{
						if (!m_actors[j].m_AI.IsParrying() && !m_actors[i].m_AI.IsParrying())
						{
							float ax,ay,bx,by;

							ax = m_actors[i].sword_velocity_X *-1.0f;
							ay = m_actors[i].sword_velocity_Y *-1.0f;
							bx = m_actors[j].sword_velocity_X *-1.0f;
							by = m_actors[j].sword_velocity_Y *-1.0f;


							m_actors[i].sword_velocity_X = ax;
							m_actors[i].sword_velocity_Y = ay;
							m_actors[j].sword_velocity_X = bx;
							m_actors[j].sword_velocity_Y = by;

							m_actors[i].m_AI.SetParrying(sqrt(ax*ax + ay*ay));
							m_actors[j].m_AI.SetParrying(sqrt(bx*bx + by*by));


						}
					}
					else
					{
						m_actors[j].limbs[k].Hitpoints -= sword_speed * sword_speed * sword_speed* 100000.0f;

						if ((m_actors[j].limbs[k].limbType == LEFT_ARM ||
							m_actors[j].limbs[k].limbType == RIGHT_ARM ||
							m_actors[j].limbs[k].limbType == LEFT_HAND||
							m_actors[j].limbs[k].limbType == RIGHT_HAND || 
							m_actors[j].limbs[k].limbType == LEFT_LEG || 
							m_actors[j].limbs[k].limbType == RIGHT_LEG || 
							m_actors[j].limbs[k].limbType == LEFT_FOOT  ||
							m_actors[j].limbs[k].limbType == RIGHT_FOOT) &&(m_actors[j].limbs[k].Hitpoints < 0.0f))
							m_actors[j].limbs[k].Hitpoints = 1.0f;



						if (m_actors[j].limbs[k].Hitpoints < 0.0f)
						{
							m_actors[j].limbs[k].Hitpoints = 0.0f;	
							CorpseStruct * corpse = new CorpseStruct;
							PrepareCorpse(m_actors[j],m_actors[j].limbs[k],m_actors[i].sword_velocity_X,m_actors[i].sword_velocity_Y,corpse);
							AddCorpse(corpse);

							if (IsDeadActor(j))
								KillActor(j,m_actors[i].sword_velocity_X,m_actors[i].sword_velocity_Y);

						}
					}
				}			


			}



		}


	}
}



void GameModelClass::ConstrainLimb(int actor, int l1, int l2)
{
	D3DXVECTOR3 l1b = m_actors[actor].limbs[l1].limbBegin;
	D3DXVECTOR3 l1a = m_actors[actor].limbs[l1].limbAngle;
	float l = m_actors[actor].limbs[l1].limbLength;

	m_actors[actor].limbs[l2].limbBegin = GeometryClass::GetEnd(l1b,l1a,l);

}


void GameModelClass::ConstrainJoints(int i)
{
	if (i < 0 || i > ACTOR_COUNT-1)
		return;

	if (m_actors[i].active)
	{
		ConstrainLimb(i,2,4);
		ConstrainLimb(i,3,5);
		ConstrainLimb(i,6,8);
		ConstrainLimb(i,7,9);
	}
}




int GameModelClass::GetActorIndexNearestEnemy(int myIndex)
{
	if (myIndex < 0 || myIndex > ACTOR_COUNT-1)
		return -1;
	if(!m_actors[myIndex].active)
		return -1;

	float d = 99999.9f;
	float closest_distance = 99999.9f;
	int closest_index = -1;


	for(int i =0;i<ACTOR_COUNT;i++)
	{
		if(m_actors[i].active && i!=myIndex && m_actors[i].team != m_actors[myIndex].team)
		{
			d = GeometryClass::Distance(m_actors[i].m_position.GetPosition(), m_actors[myIndex].m_position.GetPosition());

			if ( d < closest_distance)
			{
				closest_distance = d;
				closest_index = i;
			}
		

		}
	}


	return closest_index;

}


int GameModelClass::GetActorIndexNearestActor(int myIndex)
{
	if (myIndex < 0 || myIndex > ACTOR_COUNT-1)
		return -1;
	if(!m_actors[myIndex].active)
		return -1;

	float d = 99999.9f;
	float closest_distance = 99999.9f;
	int closest_index = -1;


	for(int i =0;i<ACTOR_COUNT;i++)
	{
		if(m_actors[i].active && i!=myIndex)
		{
			d = GeometryClass::Distance(m_actors[i].m_position.GetPosition(), m_actors[myIndex].m_position.GetPosition());

			if ( d < closest_distance)
			{
				closest_distance = d;
				closest_index = i;
			}
		

		}
	}


	return closest_index;

}

void GameModelClass::SetTeam(int actor_index, int team)
{
	if (actor_index < 0 || actor_index > ACTOR_COUNT-1)
		return;
	if(!m_actors[actor_index].active)
		return;

	m_actors[actor_index].team = team;

}

void GameModelClass::SetTeamsAllVersusCamera(int camera)
{
	for(int i=0;i<ACTOR_COUNT;i++)
	{
		if(m_actors[i].active)
		{
			m_actors[i].team = 0;

			if (i==0)
				m_actors[i].team = 1;

		}
	}

}

void GameModelClass::SetTeamsEvenOdd()
{
	for(int i=0;i<ACTOR_COUNT;i++)
	{
		if(m_actors[i].active)
		{
			m_actors[i].team = i%2;


		}
	}

}