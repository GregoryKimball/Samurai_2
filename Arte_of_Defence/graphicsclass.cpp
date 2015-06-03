////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{


	m_D3D = 0;
	m_Camera = 0;
	text_Camera = 0;
	m_Model = 0;
	m_TextureShader = 0;
	m_ColorShader = 0;
	m_LightShader = 0;
	m_TerrainShader = 0;
	m_Light = 0;

	m_Bitmap = 0;
	cursor_Bitmap = 0;
	triangle_Model=0;

	m_Text = 0;

	m_ModelList = 0;
	m_Frustum = 0;
	m_Terrain = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{


	bool result;
	D3DXMATRIX baseViewMatrix;


		
	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)	{		return false;	}
	m_Camera->SetPosition(0.0f, 6.0f, -10.0f);
	
	// Create the model object.
	m_Model = new ModelClass;
	if(!m_Model)	{		return false;	}
	triangle_Model = new ModelClass;
	if(!m_Model)	{		return false;	}


		// Initialize a base view matrix with the camera for 2D user interface rendering.

	text_Camera = new CameraClass;
	if(!text_Camera)	{		return false;	}
	text_Camera->SetPosition(0.0f, 0.0f, -1.0f);
	text_Camera->Render();
	text_Camera->GetViewMatrix(baseViewMatrix);

	


		// Create the text object.
	m_Text = new TextClass;
	if(!m_Text) 	{		return false;	}

	// Initialize the text object.
	result = m_Text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}


	
	
	result = triangle_Model->Initialize(m_D3D->GetDevice(), "../Arte_of_Defence/blender_test/triangle.txt", L"../Arte_of_Defence/blender_test/maleclothes.dds");
	if(!result)	{		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);		return false;	}


	result = m_Model->Initialize(m_D3D->GetDevice(), "../Arte_of_Defence/blender_test/01-male_whole.txt", L"../Arte_of_Defence/blender_test/malegray.dds");
	if(!result)	{		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);		return false;	}	
	
	// Create the model list object.
	m_ModelList = new ModelListClass;
	if(!m_ModelList)	{		return false;	}

	// Initialize the model list object.
	result = m_ModelList->Initialize(MODEL_LIST_COUNT);
	if(!result)	{		MessageBox(hwnd, L"Could not initialize the model list object.", L"Error", MB_OK);		return false;	}

	m_MasterModelList = new ModelClass[MASTER_MODEL_LIST_COUNT];
	result = InitializeMasterModelList();
	if(!result)	{		MessageBox(hwnd, L"Could not initialize the master model list.", L"Error", MB_OK);		return false;	}

	/*for (int i = 0; i< m_ModelList->GetModelCount(); i++)
	{
		
		if (i==1)
			result = m_ModelList->InitializeModel(i,m_D3D->GetDevice(), "../Arte_of_Defence/blender_test/01-male_whole.txt", L"../Arte_of_Defence/blender_test/malegray.dds");

		if (i==2)
			result = m_ModelList->InitializeModel(i,m_D3D->GetDevice(), "../Arte_of_Defence/blender_test/02-head2.txt", L"../Arte_of_Defence/blender_test/malegray.dds");


		if (i==0)
			result = m_ModelList->InitializeModel(i,m_D3D->GetDevice(), "../Arte_of_Defence/blender_test/02-torso2.txt", L"../Arte_of_Defence/blender_test/malegray.dds");


		if (i==3)
			result = m_ModelList->InitializeModel(i,m_D3D->GetDevice(), "../Arte_of_Defence/blender_test/01-male_whole.txt", L"../Arte_of_Defence/blender_test/malegray.dds");

		if(!result)	{		MessageBox(hwnd, L"Could not initialize the modellist object.", L"Error", MB_OK);		return false;	}	

	}*/
	
	





	






	// Create the texture shader object.
	m_TextureShader = new TextureShaderClass;
	if(!m_TextureShader)	{		return false;	}
	result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)	{		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);		return false;	}

	m_ColorShader = new ColorShaderClass;
	if(!m_ColorShader)	{		return false;	}
	result = m_ColorShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)	{		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);		return false;	}

	// Create the terrain shader object.
	m_TerrainShader = new TerrainShaderClass;
	if(!m_TerrainShader)	{		return false;	}
	result = m_TerrainShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)	{		MessageBox(hwnd, L"Could not initialize the terrain shader object.", L"Error", MB_OK);		return false;	}



		// Create the bitmap object.
	m_Bitmap = new BitmapClass;
	if(!m_Bitmap)	{		return false;	}
	result = m_Bitmap->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, L"../Arte_of_Defence/blender_test/maleclothes.dds", 256, 256);
	if(!result)	{		MessageBox(hwnd, L"Could not initialize the m_Bitmap object.", L"Error", MB_OK);		return false;	}

	cursor_Bitmap = new BitmapClass;
	if(!cursor_Bitmap)	{		return false;	}
	result = cursor_Bitmap->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, L"../Arte_of_Defence/blender_test/cursor2.dds", 60, 60);
	if(!result)	{		MessageBox(hwnd, L"Could not initialize the cursor_Bitmap object.", L"Error", MB_OK);		return false;	}


	


	
	m_LightShader = new LightShaderClass;
	if(!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if(!m_Light)
	{
		return false;
	}


	// Initialize the light object.
	
	//ambient is baseline illumination
	//diffuse is directional 
	//specular
	
	m_Light->SetAmbientColor(0.55f, 0.55f, 0.55f, 0.1f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(-1.0f, -0.0f, 1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(100.0f);








//Here we create the new FrustumClass object. It doesn't need any initialization since that is done every frame using the ConstructFrustum function.

	// Create the frustum object.
	m_Frustum = new FrustumClass;
	if(!m_Frustum)
	{
		return false;
	}





	// Create the terrain object.
	m_Terrain = new TerrainClass;
	if(!m_Terrain)	{		return false;	}
	// Initialize the terrain object.
	
	result = m_Terrain->Initialize(m_D3D->GetDevice(), "../Arte_of_Defence/blender_test/terrain2.bmp", L"../Arte_of_Defence/blender_test/tallahassee_grass.bmp");
	//result = m_Terrain->Initialize(m_D3D->GetDevice());
	if(!result)	{		MessageBox(hwnd, L"Could not initialize the terrain object.", L"Error", MB_OK);		return false;	}





	return true;
}


void GraphicsClass::Shutdown()
{

	// Release the bitmap object.
	
	// Release the frustum object.
	if(m_Frustum)
	{
		delete m_Frustum;
		m_Frustum = 0;
	}

	// Release the model list object.
	if(m_ModelList)
	{
		m_ModelList->Shutdown();
		delete m_ModelList;
		m_ModelList = 0;
	}



	
	if(m_Bitmap)
	{
		m_Bitmap->Shutdown();
		delete m_Bitmap;
		m_Bitmap = 0;
	}

	if(cursor_Bitmap)
	{		cursor_Bitmap->Shutdown();		delete cursor_Bitmap;		cursor_Bitmap = 0;	}
	

	// Release the texture shader object.
	if(m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	if(m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}


	// Release the terrain shader object.
	if(m_TerrainShader)
	{
		m_TerrainShader->Shutdown();
		delete m_TerrainShader;
		m_TerrainShader = 0;
	}


	// Release the light object.
	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the light shader object.
	if(m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}


	// Release the modelobject.
	if(m_Model)	{		m_Model->Shutdown();		delete m_Model;		m_Model = 0;	}
	if(triangle_Model)	{		triangle_Model->Shutdown();		delete triangle_Model;		triangle_Model = 0;	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	if(m_Text)
	{
		m_Text->Shutdown();
		delete m_Text;
		m_Text = 0;
	}

	// Release the camera object.
	if(text_Camera)
	{
		delete text_Camera;
		text_Camera = 0;
	}


	// Release the terrain object.
	if(m_Terrain)	{		m_Terrain->Shutdown();		delete m_Terrain;		m_Terrain = 0;	}


	return;
}


bool GraphicsClass::Frame(int fps, int cpu, float frameTime,int mouseX, int mouseY, int forceX, int forceY, int forceZ, int Camera_Actor_Index)
{
	
	bool result;
	
	result = m_Text->SetMousePosition(mouseX, mouseY, m_D3D->GetDeviceContext());
	if(!result)	{		return false;	}
	//m_Camera->SetPosition(0.0f, 0.0f, -10.0f);

	static float rotation = 0.0f;
	
	// Update the rotation variable each frame.
	//rotation += (float)D3DX_PI * 0.01f;
	if(rotation > 360.0f)
	{
		rotation -= 360.0f;
	}


	


	result = m_Text->SetFps(fps, m_D3D->GetDeviceContext());
	if(!result)	{		return false;	}

	// Set the cpu usage.
	result = m_Text->SetCpu(cpu, m_D3D->GetDeviceContext());	
	if(!result)	{		return false;	}


	


	//set camera position
	result = m_Text->SetCameraPosition(m_Camera->GetPosX(),m_Camera->GetPosY(),m_Camera->GetPosZ(),m_Camera->GetRotX(),m_Camera->GetRotY(),m_Camera->GetRotZ(), m_D3D->GetDeviceContext());			
	if(!result)	{		return false;	}


	result = m_Text->SetAccelerometer(forceX,forceY,forceZ, m_D3D->GetDeviceContext());			
	if(!result)	{		return false;	}





	result = Render(rotation,mouseX,mouseY);
	if(!result)	{		return false;	}


	



	return true;
}




bool GraphicsClass::InitializeMasterModelList()
{
	bool result;

	for(int i =0; i<MASTER_MODEL_LIST_COUNT;i++)
	{
		
		switch (i) 
		{
			case 0:
				result = m_MasterModelList[i].Initialize(m_D3D->GetDevice(),"../Arte_of_Defence/blender_test/02-head3.txt", L"../Arte_of_Defence/blender_test/malegray.dds");
				break;
			case 1:
				result = m_MasterModelList[i].Initialize(m_D3D->GetDevice(),"../Arte_of_Defence/blender_test/02-torso3.txt", L"../Arte_of_Defence/blender_test/malegray.dds");			
				break;		 
			case 2:
				result = m_MasterModelList[i].Initialize(m_D3D->GetDevice(),"../Arte_of_Defence/blender_test/02-left_arm3.txt", L"../Arte_of_Defence/blender_test/malegray.dds");			
				break;		 
			case 3:
				result = m_MasterModelList[i].Initialize(m_D3D->GetDevice(),"../Arte_of_Defence/blender_test/02-right_arm3.txt", L"../Arte_of_Defence/blender_test/malegray.dds");			
				break;		 
			case 4:
				result = m_MasterModelList[i].Initialize(m_D3D->GetDevice(),"../Arte_of_Defence/blender_test/02-left_hand3.txt", L"../Arte_of_Defence/blender_test/malegray.dds");			
				break;		 
			case 5:
				result = m_MasterModelList[i].Initialize(m_D3D->GetDevice(),"../Arte_of_Defence/blender_test/02-right_hand3.txt", L"../Arte_of_Defence/blender_test/malegray.dds");			
				break;		 
			case 6:
				result = m_MasterModelList[i].Initialize(m_D3D->GetDevice(),"../Arte_of_Defence/blender_test/02-left_leg3.txt", L"../Arte_of_Defence/blender_test/malegray.dds");			
				break;		 
			case 7:
				result = m_MasterModelList[i].Initialize(m_D3D->GetDevice(),"../Arte_of_Defence/blender_test/02-right_leg3.txt", L"../Arte_of_Defence/blender_test/malegray.dds");			
				break;		 
			case 8:
				result = m_MasterModelList[i].Initialize(m_D3D->GetDevice(),"../Arte_of_Defence/blender_test/02-left_foot3.txt", L"../Arte_of_Defence/blender_test/malegray.dds");			
				break;		 
			case 9:
				result = m_MasterModelList[i].Initialize(m_D3D->GetDevice(),"../Arte_of_Defence/blender_test/02-right_foot3.txt", L"../Arte_of_Defence/blender_test/malegray.dds");			
				break;	
			case 10:
				result = m_MasterModelList[i].Initialize(m_D3D->GetDevice(),"../Arte_of_Defence/blender_test/01-sword3.txt", L"../Arte_of_Defence/blender_test/01-sword.dds");			
				break;	
			
		}

		if (!result) return result;
	}

	

	return true;
}

bool GraphicsClass::Render(float rotation,int mouseX, int mouseY)
{


	//D3DXMATRIX viewMatrix, projectionMatrix, worldMatrix;
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;

	D3DXMATRIX translationMatrix, rotationMatrix;

	D3DXVECTOR4 color;
	bool renderModel,result;
	int modelCount, renderCount,  index;
	float positionX, positionY, positionZ, rotationX, rotationY, rotationZ, radius;


	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.1f, 0.1f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();
	m_Camera->GetViewMatrix(viewMatrix);

	m_D3D->GetWorldMatrix(translationMatrix);
	rotationMatrix = translationMatrix;

	m_D3D->GetProjectionMatrix(projectionMatrix);
	
	//	m_Camera->Render();
	//m_Camera->GetViewMatrix(viewMatrix);



		// Construct the frustum.
	m_Frustum->ConstructFrustum(SCREEN_DEPTH, projectionMatrix, viewMatrix);

	// Get the number of models that will be rendered.
	modelCount = m_ModelList->GetModelCount();





	// Initialize the count of models that have been rendered.
	renderCount = 0;

	// Go through all the models and render them only if they can be seen by the camera view.
	
//	ModelClass* renderingModel;

	for(index=0; index<modelCount; index++)
	{
		// Get the position and color of the sphere model at this index.

		

		m_ModelList->GetData(index, positionX, positionY, positionZ, rotationX, rotationY, rotationZ, color);

		// Set the radius of the sphere to 1.0 since this is already known.
		radius = 10.0f;

		// Check if the sphere model is in the view frustum.
		renderModel = m_Frustum->CheckSphere(positionX, positionY, positionZ, radius);

		// If it can be seen then render it, if not skip this model and check the next sphere.
		if(renderModel && m_ModelList->IsActive(index))
		{
			
			//apply the rotation of the model to the matrix

			D3DXMatrixRotationYawPitchRoll(&rotationMatrix, rotationY, rotationX, rotationZ);
			
			// Move the model to the location it should be rendered at. for the translation
			D3DXMatrixTranslation(&translationMatrix, positionX, positionY, positionZ); 

			


			// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
			
			//m_Model->Render(m_D3D->GetDeviceContext());
			
			
			m_ModelList->RenderModel(index,m_D3D->GetDeviceContext());
			

			//combine the rotation and translation movements by matrix multiplication
			worldMatrix = rotationMatrix * translationMatrix;

			//m_Light->GetDiffuseColor()




		/*	m_LightShader->Render(m_D3D->GetDeviceContext(), m_ModelList->GetIndexCount(index), worldMatrix, viewMatrix, projectionMatrix, 
					      m_ModelList->GetTexture(index), m_Light->GetDirection(), m_Light->GetAmbientColor(), color, 
				       m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());*/

				m_LightShader->Render(m_D3D->GetDeviceContext(), m_ModelList->GetIndexCount(index), worldMatrix, viewMatrix, projectionMatrix, 
					      m_ModelList->GetTexture(index), m_Light->GetDirection(), color, color, 
				       m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());

			// Reset to the original world matrix.
			m_D3D->GetWorldMatrix(worldMatrix);

			// Since this model was rendered then increase the count for this frame.
			renderCount++;
		}
	}
	
	result = m_Text->SetRenderCount(renderCount, m_D3D->GetDeviceContext());
	if(!result)	{		return false;	}





	
	D3DXMatrixRotationY(&worldMatrix, rotation);
	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	triangle_Model->Render(m_D3D->GetDeviceContext());
	
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), triangle_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
				       triangle_Model->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), 
				       m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if(!result)
	{
		return false;
	}
	


	/*
	m_Model->Render(m_D3D->GetDeviceContext());
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), triangle_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
				       m_Model->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), 
				       m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if(!result)
	{
		return false;
	}

	*/





	// Render the terrain buffers.
	m_Terrain->Render(m_D3D->GetDeviceContext());

	// Render the terrain using the terrain shader.
	result = m_TerrainShader->Render(m_D3D->GetDeviceContext(), m_Terrain->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
					 m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), m_Light->GetDirection(), m_Terrain->GetTexture());
	if(!result)
	{
		return false;
	}
	if(!result)
	{
		return false;
	}




	// Render the model using the color shader.
//	result = m_ColorShader->Render(m_D3D->GetDeviceContext(), m_Terrain->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
	//if(!result)	{		return false;	}
	





	m_D3D->GetOrthoMatrix(orthoMatrix);
	m_D3D->TurnZBufferOff();
	m_D3D->TurnOnAlphaBlending();


	text_Camera->Render();
	text_Camera->GetViewMatrix(viewMatrix);

	// Render the text string of the render count.
	//m_Text->Render(m_D3D->GetDevice(), worldMatrix, orthoMatrix);

	

	
	result = m_Text->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	if(!result)	{		return false;	}	


	
	
	result = m_Bitmap->Render(m_D3D->GetDeviceContext(), 100, 600);
	if(!result)	{		return false;	}
	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Bitmap->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, m_Bitmap->GetTexture());
	if(!result)	{		return false;	}


	result = m_ColorShader->Render(m_D3D->GetDeviceContext(), 0, worldMatrix, viewMatrix, projectionMatrix);
	if(!result)	{		return false;	}



	result = cursor_Bitmap->Render(m_D3D->GetDeviceContext(), mouseX, mouseY);
	if(!result)	{		return false;	}
	result = m_TextureShader->Render(m_D3D->GetDeviceContext(), cursor_Bitmap->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, cursor_Bitmap->GetTexture());
	if(!result)	{		return false;	}




	m_D3D->TurnOffAlphaBlending();
	m_D3D->TurnZBufferOn();










	m_D3D->EndScene();


	return true;
}




int GraphicsClass::AddModel(char* modelFilename, WCHAR* textureFilename)
{
	return m_ModelList->AddModel(m_D3D->GetDevice(), modelFilename, textureFilename);
}

int GraphicsClass::AddModel(int master_index)
{
	return m_ModelList->AddModel(m_D3D->GetDevice(), &m_MasterModelList[master_index]);
}


void GraphicsClass::DeactivateModel(int j)
{
	m_ModelList->Deactivate(j);
}
void GraphicsClass::ActivateModel(int j)
{
	m_ModelList->Activate(j);
}


void GraphicsClass::MoveCamera(float delx, float dely ,float delz)
{
	D3DXVECTOR3 d=m_Camera->GetPosition();	
	D3DXVECTOR3 l,move;

	float yaw, pitch, roll;
	D3DXMATRIX rotationMatrix;


	move.x=delx;
	move.y=dely;
	move.z=delz;

	pitch = m_Camera->GetRotation().x;
	yaw   = m_Camera->GetRotation().y;
	roll  = m_Camera->GetRotation().z;

	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);


	D3DXVec3TransformCoord(&move, &move, &rotationMatrix);
	
	
	m_Camera->SetPosition(d.x+move.x,  d.y+move.y,  d.z+move.z);
}

void GraphicsClass::RotateCamera(float delx, float dely ,float delz)
{
	D3DXVECTOR3 d=m_Camera->GetRotation();	


	if(d.x+delx > 360.0f)
		delx -= 360.0f;
	if(d.x+delx<0.0f)
		delx += 360.0f;

	if(d.y+dely > 360.0f)
		dely -= 360.0f;
	if(d.y+dely<0)
		dely += 360;

	if(d.z+delz > 360.0f)
		delz -= 360.0f;
	if(d.z+delz<0)
		delz += 360;





	m_Camera->SetRotation(d.x+delx,  d.y+dely,  d.z+delz);
}


void GraphicsClass::SetCameraPosition(float x,float y,float z)
{

	m_Camera->SetPosition(x,y,z);
}



void GraphicsClass::SetCameraRotation(float p,float h,float t)
{
	m_Camera->SetRotation(p,h,t);
}



void GraphicsClass::SetModelPosition(int index, float x,float y,float z)
{

	
	m_ModelList->SetModelPosition(index, x,y,z);
}

void GraphicsClass::SetModelRotation(int index, float x,float y,float z)
{

	
	m_ModelList->SetModelRotation(index, x,y,z );
}

void GraphicsClass::SetModelColor(int index , float r ,float g ,float b , float a)
{
		m_ModelList->SetModelColor(index, r,g,b,a);
}

float GraphicsClass::GetTerrainHeight(float x, float z)
{

	return m_Terrain->GetTerrainHeight(x,z);
}