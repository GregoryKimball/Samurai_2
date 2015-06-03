///////////////////////////////////////////////////////////////////////////////
// Filename: modellistclass.h
///////////////////////////////////////////////////////////////////////////////
#ifndef _MODELLISTCLASS_H_
#define _MODELLISTCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>
#include <stdlib.h>
#include <time.h>
#include "modelclass.h"
//#include "systemclass.h"




///////////////////////////////////////////////////////////////////////////////
// Class name: ModelListClass
///////////////////////////////////////////////////////////////////////////////
class ModelListClass
{
private:
	struct ModelInfoType
	{
		D3DXVECTOR4 color;
		float positionX, positionY, positionZ;
		float rotationX, rotationY, rotationZ;
		ModelClass* m_Model;
		int actor_index;
		int limb_index;
		bool active;
	};

public:
	ModelListClass();
	ModelListClass(const ModelListClass&);
	~ModelListClass();

	bool Initialize(int);
	

	void Shutdown();

	int GetModelCount();
	void GetData(int, float&, float&, float&, D3DXVECTOR4&);
	bool IsActive(int);
	void Deactivate(int);
	void Activate(int);
	void GetData(int, float&, float&, float&, float&, float&, float&, D3DXVECTOR4&);

	void MoveModel(int, float, float, float);
		
	bool InitializeModel(int, ID3D11Device*, char*, WCHAR*);
	int ModelListClass::AddModel(ID3D11Device*, char*, WCHAR*);
	int ModelListClass::AddModel(ID3D11Device* , ModelClass* );
	void RenderModel(int, ID3D11DeviceContext*);
	int GetIndexCount(int);
	ID3D11ShaderResourceView* GetTexture(int);

	

void ModelListClass::MoveModelPosition(int , float, float , float );
void ModelListClass::SetModelPosition(int , float, float , float );
void ModelListClass::MoveModelRotation(int,  float, float , float );
void ModelListClass::SetModelRotation(int , float, float , float );

void ModelListClass::SetModelColor(int , float, float , float, float );


private:
	int m_modelCount;
	ModelInfoType* m_ModelInfoList;	
	
};

#endif