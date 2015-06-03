
////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


//////////////
// INCLUDES //
//////////////
//#include <windows.h>
///////////////////////
// MY CLASS INCLUDES //
///////////////////////



#include "d3dclass.h"
#include "cameraclass.h"
#include "modellistclass.h"
#include "modelclass.h"

#include "textclass.h"
#include "colorshaderclass.h"
#include "textureshaderclass.h"

#include "lightshaderclass.h"
#include "terrainshaderclass.h"

#include "lightclass.h"
#include "bitmapclass.h"



#include "frustumclass.h"
#include "terrainclass.h"




/////////////
// GLOBALS //
/////////////


//const bool FULL_SCREEN = true;
const bool FULL_SCREEN = false;

const bool VSYNC_ENABLED = true;
//const bool VSYNC_ENABLED = false;

const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

const int MODEL_LIST_COUNT = 1000;
const int MASTER_MODEL_LIST_COUNT = 11;

//We'll need these four globals to start with.

////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	bool GraphicsClass::InitializeMasterModelList();
	void Shutdown();
	//bool Frame();
	bool Frame(int, int, float, int, int, int, int, int,int);
	bool Render(float,int,int);

	void MoveCamera(float,float,float);
	void RotateCamera(float,float,float);
	void SetCameraPosition(float,float,float);
	void SetCameraRotation(float,float,float);
	
	int GraphicsClass::AddModel(char*, WCHAR*);
	int GraphicsClass::AddModel(int);
	void GraphicsClass::DeactivateModel(int);
	void GraphicsClass::ActivateModel(int);
	void SetModelPosition(int, float,float,float);
	void SetModelRotation(int, float,float,float);
	void SetModelColor(int, float,float,float, float);

	float GetTerrainHeight(float, float);

//private:
	//bool Render();
	//bool Render(float);

private:



	D3DClass* m_D3D;
	CameraClass* m_Camera;
	CameraClass* text_Camera;
	
	
	ModelClass* m_Model;
	ModelClass* triangle_Model;
	
	ModelClass* m_MasterModelList;
	
	ColorShaderClass* m_ColorShader;

	TextureShaderClass* m_TextureShader;
	LightShaderClass* m_LightShader;
	TerrainShaderClass* m_TerrainShader;

	LightClass* m_Light;
	BitmapClass* m_Bitmap;
	BitmapClass* cursor_Bitmap;
	
	TextClass* m_Text;

	
	FrustumClass* m_Frustum;
	TerrainClass* m_Terrain;

public:

		ModelListClass* m_ModelList;

};

#endif
