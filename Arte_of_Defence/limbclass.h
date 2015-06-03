#ifndef _LIMBCLASS_H_
#define _LIMBCLASS_H_


#include <d3d11.h>
#include <d3dx10math.h>



	enum LimbTypeEnum
	{
		HEAD, TORSO, LEFT_ARM, RIGHT_ARM, LEFT_HAND, RIGHT_HAND, LEFT_LEG, RIGHT_LEG, LEFT_FOOT, RIGHT_FOOT, SWORD
	};




class LimbClass
{

public:




		LimbTypeEnum limbType;
		float Hitpoints;		
		float HitpointsMax;		
		D3DXVECTOR3 limbBegin;
		float limbLength;
		float limbWidth;
		D3DXVECTOR3 limbAngle;
		int model_index;	
		bool attached;

		LimbClass();
		LimbClass(const LimbClass&);
		~LimbClass();
		bool LimbClass::Initialize();


};


#endif