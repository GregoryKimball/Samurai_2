#ifndef _ACTORCLASS_H_
#define _ACTORCLASS_H_


#include <d3d11.h>
#include <d3dx10math.h>
#include "positionclass.h"
#include "GeometryClass.h"
#include "aiclass.h"
#include "limbclass.h"
#include "textclass.h"
#include <string>
#include <cstdlib>

const int LIMB_COUNT = 11;



class ActorClass
{

public:



	

	LimbClass* limbs;		
	PositionClass m_position;
	bool active;

	float strength;
	float dexterity;
	float sword_setpoint_X;
	float sword_setpoint_Y;
	float sword_position_X;
	float sword_position_Y;
	float sword_velocity_X;
	float sword_velocity_Y;
	float sword_acc_X;
	float sword_acc_Y;


	int team;
	AIClass m_AI;

	ActorClass();
	ActorClass(const ActorClass&);
	~ActorClass();

	bool ActorClass::Initialize();

	LimbClass* ActorClass::KillActor(float,float);
	bool ActorClass::IsDead();
	bool ActorClass::Heal();
	


	void ActorClass::UpdateSword(float, float );
	void ActorClass::SyncModelToActor(int, D3DXVECTOR3& , D3DXVECTOR3&);
	void ActorClass::ResetLimbs();


private:

};

#endif