////////////////////////////////////////////////////////////////////////////////
// Filename: gamemodelclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GAMEMODELCLASS_H_
#define _GAMEMODELCLASS_H_




//////////////
// INCLUDES //
//////////////

#include <d3d11.h>
#include <d3dx10math.h>
#include "actorclass.h"
#include "positionclass.h"
#include "GeometryClass.h"
#include "aiclass.h"

#include "textclass.h"
#include <string>
#include <cstdlib>






const int ACTOR_COUNT = 15;
const int CORPSE_COUNT = 200;


class GameModelClass
{

	
public:
	
	

	


	struct CorpseStruct
	{
		LimbClass limb;		
		PositionClass m_position;
		bool active;
		int team;
	};

	


	GameModelClass();
	GameModelClass(const GameModelClass&);
	~GameModelClass();
	bool Initialize();
	int AddActor();

	bool GameModelClass::IsDeadActor(int);

	void PrepareCorpse(ActorClass&, LimbClass&, float , float , GameModelClass::CorpseStruct*);
	int AddCorpse(GameModelClass::CorpseStruct*);
	void LinkLimbToModel(int, int, int);
	void GameModelClass::UpdateSword(int , float, float);
	
	void GameModelClass::SyncModelToActor(int , int , D3DXVECTOR3& , D3DXVECTOR3& , D3DXVECTOR3& );

	void GameModelClass::ResetLimbs(int );
	void GameModelClass::CheckCollisions();
	void GameModelClass::ConstrainJoints(int);
	D3DXVECTOR3 GameModelClass::GetColorFromHitpoints(float , float,int);
	
	void GameModelClass::KillActor(int, float,float);
	void GameModelClass::KillAllActors();
	void GameModelClass::HealActor(int);
	void GameModelClass::HealAllActors();


	int GetActorIndexNearestEnemy(int);
	int GetActorIndexNearestActor(int);
	void GameModelClass::SetTeam(int,int);
	void GameModelClass::SetTeamsAllVersusCamera(int);
	void GameModelClass::SetTeamsEvenOdd();

	ActorClass* m_actors;
	CorpseStruct* m_corpses;


private:

	void GameModelClass::ConstrainLimb(int, int,int);
	int Corpse_Index;

	bool GameModelClass::IsValidActor(int);


};


#endif