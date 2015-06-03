////////////////////////////////////////////////////////////////////////////////
// Filename: systemclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "systemclass.h"


SystemClass::SystemClass()
{
	m_Input = 0;
	m_Graphics = 0;
	m_Sound = 0;

	m_Fps = 0;
	m_Cpu = 0;
	m_Timer = 0;
	m_Position = 0;
	m_Accelerometer = 0;


}


SystemClass::SystemClass(const SystemClass& other)
{
}


SystemClass::~SystemClass()
{
}


bool SystemClass::Initialize()
{
	int screenWidth, screenHeight;
	bool result;


	// Initialize the width and height of the screen to zero before sending the variables into the function.
	screenWidth = 0;
	screenHeight = 0;

	// Initialize the windows api.
	InitializeWindows(screenWidth, screenHeight);
	WINDOW_WIDTH = screenWidth;
	WINDOW_HEIGHT = screenHeight;

	// Create the input object.  This object will be used to handle reading the keyboard input from the user.
	m_Input = new InputClass;
	if(!m_Input)
	{
		return false;
	}

	// Initialize the input object.
	//m_Input->Initialize();
	result = m_Input->Initialize(m_hinstance, m_hwnd, screenWidth, screenHeight);
	if(!result)
	{
		MessageBox(m_hwnd, L"Could not initialize the input object.", L"Error", MB_OK);
		return false;
	}


	
	m_Graphics = new GraphicsClass;
	if(!m_Graphics) {		return false;	}
	result = m_Graphics->Initialize(screenWidth, screenHeight, m_hwnd);
	if(!result)	{		return false;	}
	



	m_Sound = new SoundClass;
	if(!m_Sound)	{		return false;	}
	result = m_Sound->Initialize(m_hwnd);
	if(!result)	{		MessageBox(m_hwnd, L"Could not initialize Direct Sound.", L"Error", MB_OK);		return false;	}
	



	m_Fps = new FpsClass;
	if(!m_Fps)	{		return false;	}
	m_Fps->Initialize();

	m_Cpu = new CpuClass;
	if(!m_Cpu)	{		return false;	}
	m_Cpu->Initialize();

	m_Timer = new TimerClass;
	if(!m_Timer)	{		return false;	}
	result = m_Timer->Initialize();
	if(!result)	{		MessageBox(m_hwnd, L"Could not initialize the Timer object.", L"Error", MB_OK);		return false;	}
	


	
	m_Position = new PositionClass;
	if(!m_Position)	{		return false;	}

	m_Position->Initialize();
	
	m_Position->SetPosition(10,10,-30);
	m_Position->m_floating = true;


	m_Accelerometer = new AccelerometerClass;
	if (!m_Accelerometer) {return false;}
	result = m_Accelerometer->Initialize();
	//if(!result)	{		MessageBox(m_hwnd, L"Could not initialize the Accelerometer object.", L"Error", MB_OK);		return false;	}



	m_GameModel = new GameModelClass;
	if(!m_GameModel)	{		return false;	}
	result = m_GameModel->Initialize();
	if(!result)	{		MessageBox(m_hwnd, L"Could not initialize the GameModel object.", L"Error", MB_OK);		return false;	}



	Camera_Actor_Index = -1;
	Camera_Actor_Distance = -20;
	Camera_Actor_Angle = 0.0f;


	return true;
}



void SystemClass::Shutdown()
{

	// Release the sound object.
	if(m_Sound)	{		m_Sound->Shutdown();		delete m_Sound;		m_Sound = 0;	}	
	// Release the graphics object.
	if(m_Graphics)	{		m_Graphics->Shutdown();		delete m_Graphics;		m_Graphics = 0;	}	
	// Release the input object.
	if(m_Input)	{		m_Input->Shutdown();		delete m_Input;		m_Input = 0;	}
	// Release the timer object
	if(m_Timer)	{		delete m_Timer;		m_Timer = 0;	}
	// Release the cpu object.
	if(m_Cpu)	{		m_Cpu->Shutdown();		delete m_Cpu;		m_Cpu = 0;	}
	// Release the fps object.
	if(m_Fps)	{		delete m_Fps;		m_Fps = 0;	}
	// Release the position object.
	if(m_Position)	{		delete m_Position;		m_Position = 0;	}
	
	if(m_Accelerometer) 	{		delete m_Accelerometer;		m_Accelerometer = 0;	}

	// Shutdown the window.
	ShutdownWindows();
	
	return;
}


void SystemClass::Run()
{
	MSG msg;
	bool done, result;


	// Initialize the message structure.
	ZeroMemory(&msg, sizeof(MSG));
	
	// Loop until there is a quit message from the window or the user.
	done = false;
	while(!done)
	{
		// Handle the windows messages.
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// If windows signals to end the application then exit out.
		if(msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			// Otherwise do the frame processing.
			result = Frame();
			if(!result)
			{
				done = true;
			}
		}



		// Check if the user pressed escape and wants to quit.
		if(m_Input->IsEscapePressed() == true)
		{
			done = true;
		}


	}

	return;

}

bool SystemClass::Frame()
{
	bool result;
	int mouseX,mouseY;
	int forceX=0,forceY=0,forceZ=0;
	float f=0.0f;


	m_Timer->Frame();
	m_Fps->Frame();
	m_Cpu->Frame();
	m_Accelerometer->Frame();

	


	
	m_GameModel->SetTeamsAllVersusCamera(Camera_Actor_Index);
	//m_GameModel->SetTeamsEvenOdd();

	

	result = HandleInput(m_Timer->GetTime());
	if(!result)	{		return false;	}

	result = HandleAI(m_Timer->GetTime());
	if(!result)	{		return false;	}



	// Get the location of the mouse from the input object,
	
	m_Input->GetMouseLocation(mouseX, mouseY);
	
	AdvancePositions(m_Timer->GetTime());
	
	

	SyncActorAndModel();
	SyncCameraAndActor();
	m_GameModel->CheckCollisions();

	//m_Accelerometer->GetForce(forceX,forceY,forceZ);
	

	result = CleanUpModels();

	result = m_Graphics->Frame(m_Fps->GetFps(), m_Cpu->GetCpuPercentage(), m_Timer->GetTime(),mouseX, mouseY, forceX,forceY, forceZ, Camera_Actor_Index);

	

	if(!result)
	{
		return false;
	}

	

	return true;
}

bool SystemClass::HandleInput(float frameTime)
{
	

	//if (frameTime<1) frameTime=1;

	bool result;
	 //Do the input frame processing.
	result = m_Input->Frame();
	if(!result)
	{		return false;	}
	
	
	
	
	
	
	
	bool keyDown;
	float posX, posY, posZ, rotX, rotY, rotZ;
//The very first thing that is done is the frame time is set in the PositionClass object. The reason being is that the frame time is required by all the following movement calculation functions. If it is not set then the movement will not be accurate.

	// Set the frame time for calculating the updated position.
	
	
	
	
	



//Next the user input is determined for each of the eight movement types. The forward, backward, turn left, and turn right functions are updated by the arrow keys. The up and down movement functions are updated by the A and Z keys. The look up and look down rotation functions are updated by the PgUp and PgDn keys. If the user is pressing the key then a true boolean value will be sent to the appropriate function. If not then false is sent to each. This allows us to accelerate if the user is holding down the movement key or decelerate if the user is not holding down that movement key.

	// Handle the input.
	keyDown = m_Input->IsQPressed();
	m_Position->TurnLeft(keyDown);
	if (Camera_Actor_Index > -1)
		m_GameModel->m_actors[Camera_Actor_Index].m_position.TurnLeft(keyDown);
	
	keyDown = m_Input->IsEPressed();
	m_Position->TurnRight(keyDown);
	if (Camera_Actor_Index > -1)
		m_GameModel->m_actors[Camera_Actor_Index].m_position.TurnRight(keyDown);

	keyDown = m_Input->IsAPressed();
	m_Position->StrafeLeft(keyDown);
	if (Camera_Actor_Index > -1)
		m_GameModel->m_actors[Camera_Actor_Index].m_position.StrafeLeft(keyDown);

	keyDown = m_Input->IsDPressed();
	m_Position->StrafeRight(keyDown);
	if (Camera_Actor_Index > -1)
		m_GameModel->m_actors[Camera_Actor_Index].m_position.StrafeRight(keyDown);


	keyDown = m_Input->IsWPressed();
	m_Position->MoveForward(keyDown);
	if (Camera_Actor_Index > -1)
		m_GameModel->m_actors[Camera_Actor_Index].m_position.MoveForward(keyDown);

	keyDown = m_Input->IsSPressed();
	m_Position->MoveBackward(keyDown);
	if (Camera_Actor_Index > -1)
		m_GameModel->m_actors[Camera_Actor_Index].m_position.MoveBackward(keyDown);

	keyDown = m_Input->IsKeyPressed(DIK_SPACE);
	m_Position->MoveUpward(keyDown);
	if (Camera_Actor_Index > -1)
		m_GameModel->m_actors[Camera_Actor_Index].m_position.MoveUpward(keyDown);

	keyDown = m_Input->IsKeyPressed(DIK_LCONTROL);
	m_Position->MoveDownward(keyDown);
	if (Camera_Actor_Index > -1)
		m_GameModel->m_actors[Camera_Actor_Index].m_position.MoveDownward(keyDown);


	keyDown = m_Input->IsPgUpPressed();
	m_Position->LookUpward(keyDown);
	if (Camera_Actor_Index > -1)
		m_GameModel->m_actors[Camera_Actor_Index].m_position.LookUpward(keyDown);

	keyDown = m_Input->IsPgDownPressed();
	m_Position->LookDownward(keyDown);
	if (Camera_Actor_Index > -1)
		m_GameModel->m_actors[Camera_Actor_Index].m_position.LookDownward(keyDown);

	keyDown = m_Input->IsCPressed();
	m_Position->RollLeft(keyDown);
	if (Camera_Actor_Index > -1)
		m_GameModel->m_actors[Camera_Actor_Index].m_position.RollLeft(keyDown);

	keyDown = m_Input->IsVPressed();
	m_Position->RollRight(keyDown);
	if (Camera_Actor_Index > -1)
		m_GameModel->m_actors[Camera_Actor_Index].m_position.RollRight(keyDown);
	


	


	//After the movement for this frame has been calculated we then get the position and rotation from the PositionObject and update the CameraClass and TextClass object with the new viewing position.

	// Get the view point position/rotation.
	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);

	// Set the position of the camera.
	m_Graphics->SetCameraPosition(posX, posY, posZ);
	m_Graphics->SetCameraRotation(rotX, rotY, rotZ);


	if (m_Input->WasKeyPressed(DIK_N)) 
	{
		Camera_Actor_Angle += 0.3f;
	}

	if (m_Input->WasKeyPressed(DIK_M)) 
	{
		Camera_Actor_Angle -= 0.3f;
	}



	if (m_Input->IsKeyPressed(DIK_G)) 
	{
		bool s = m_Sound->PlayWaveFile(-1000);
	}

	if (m_Input->WasKeyPressed(DIK_H)) 
	{


		bool s = AddActor();		

	}

	
	if (m_Input->WasKeyPressed(DIK_J)) 
	{	
		m_GameModel->KillAllActors();
	}
	if (m_Input->WasKeyPressed(DIK_K)) 
	{	
		m_GameModel->HealAllActors();
	}


	/*if (m_Input->WasKeyPressed(DIK_X)) 
	{
		if (Camera_Actor_Index > -1)
			m_GameModel->m_actors[Camera_Actor_Index].m_position.SetRotY(m_GameModel->m_actors[Camera_Actor_Index].m_position.GetRotY()+3.141f);
		else
			m_Position->SetRotY(m_Position->GetRotY() +3.14f);
	}*/


	if (m_Input->WasRBracketPressed()) 
	{
		Camera_Actor_Index++;

		if (Camera_Actor_Index > ACTOR_COUNT -1)
			Camera_Actor_Index = ACTOR_COUNT -1;
	}

	if (m_Input->WasLBracketPressed()) 
	{
		Camera_Actor_Index--;

		if (Camera_Actor_Index < -1)
			Camera_Actor_Index = -1;
	}




	float mousex, mousey;
	m_Input->GetMouseAcceleration(mousex,mousey);

	int p_mousex, p_mousey;
	m_Input->GetMouseLocation(p_mousex,p_mousey);

	int forceX,forceY,forceZ;
	int forceMax = 100;
	m_Accelerometer->GetForce(forceX,forceY,forceZ);

	float sw_inputX = 0.0f;
	float sw_inputY = 0.0f;
	
	if (forceX ==0 && forceY == 0 && forceZ==0)	
	{
		sw_inputX =  (float)p_mousex/(float)WINDOW_WIDTH -0.5f;
		sw_inputY =  (float)p_mousey/(float)WINDOW_WIDTH -0.5f;	
	}
	
		
	m_GameModel->UpdateSword(Camera_Actor_Index , sw_inputX, sw_inputY);
	m_GameModel->m_actors[Camera_Actor_Index].m_AI.SetMouseInput(sw_inputX, sw_inputY);



	return true;
}//handleinput




bool SystemClass::HandleAI(float frameTime)
{
	//AIClass ai;
	//ai.Initialize();
	int enemy = -1;
	bool keyDown;
	float mx=0.0f,my=0.0f;

	for(int i = 0; i<ACTOR_COUNT;i++)
	{
		if (!m_GameModel->m_actors[i].active)
		{
			TextClass::debug_strings[i] = "";
			continue;
		}

		TextClass::debug_strings[i] = "Actor: " + TextClass::GetString(i) +"  "+ m_GameModel->m_actors[i].m_AI.GetState();
					



		m_GameModel->m_actors[i].m_AI.FrameActions(frameTime);
		



		if (i != Camera_Actor_Index)
		{
			enemy = m_GameModel->GetActorIndexNearestEnemy(i);

			if (enemy == -1)
			{
				m_GameModel->m_actors[i].m_AI.SetIdle();
				
			}
			else
			{
				m_GameModel->m_actors[i].m_AI.Frame(frameTime,
					 m_GameModel->m_actors[i].m_position,m_GameModel->m_actors[enemy].m_position,
					 1.0f,1.0f,
					 m_GameModel->m_actors[i].sword_position_X,m_GameModel->m_actors[i].sword_position_Y);			
			}



			//ai = m_GameModel->m_actors[i].m_AI;

			
			


			keyDown = m_GameModel->m_actors[i].m_AI.IsQPressed();
			m_GameModel->m_actors[i].m_position.TurnLeft(keyDown);				
			keyDown = m_GameModel->m_actors[i].m_AI.IsEPressed();
			m_GameModel->m_actors[i].m_position.TurnRight(keyDown);			
			keyDown = m_GameModel->m_actors[i].m_AI.IsAPressed();
			m_GameModel->m_actors[i].m_position.StrafeLeft(keyDown);			
			keyDown = m_GameModel->m_actors[i].m_AI.IsDPressed();
			m_GameModel->m_actors[i].m_position.StrafeRight(keyDown);			
			keyDown = m_GameModel->m_actors[i].m_AI.IsWPressed();
			m_GameModel->m_actors[i].m_position.MoveForward(keyDown);			
			keyDown = m_GameModel->m_actors[i].m_AI.IsSPressed();
			m_GameModel->m_actors[i].m_position.MoveBackward(keyDown);


			m_GameModel->m_actors[i].m_AI.GetMouseInput(mx,my);

			m_GameModel->UpdateSword(i , (float)mx , (float)my);

			
		}

		
	}

	return true;
}




bool SystemClass::AddActor()
{

	int actor_index = m_GameModel->AddActor();

	if (actor_index == -1)
		return false;
	
	int model_index = 0;

	for(int i =0;i<LIMB_COUNT;i++)
	{
		//HEAD, TORSO, LEFT_ARM, RIGHT_ARM, LEFT_HAND, RIGHT_HAND, LEFT_LEG, RIGHT_LEG, LEFT_FOOT, RIGHT_FOOT
		
		model_index = m_Graphics->AddModel(i);	
		
		m_GameModel->LinkLimbToModel(model_index, actor_index, i);
	}

	m_GameModel->m_actors[actor_index].m_position.SetPosition(	m_Position->GetPosX()+50.0f*sinf(m_Position->GetRotY()),
																m_Position->GetPosY(),
																m_Position->GetPosZ()+50.0f*cosf(m_Position->GetRotY()));

	m_GameModel->m_actors[actor_index].m_position.SetRotation(	m_Position->GetRotX(),m_Position->GetRotY() + 3.1415926f,m_Position->GetRotZ());

	m_GameModel->UpdateSword(actor_index , 0.0f,0.0f);


	

	return true;
}



bool SystemClass::SyncActorAndModel()
{
	int model_index = -1;

	D3DXVECTOR3 begin;
	D3DXVECTOR3 angle;
	D3DXVECTOR3 color;

	for(int i = 0; i<ACTOR_COUNT;i++)
	{
		if (m_GameModel->m_actors[i].active)
		{

			for(int j = 0; j<LIMB_COUNT;j++)
			{
				if (!m_GameModel->m_actors[i].limbs[j].attached)
					continue;				

				model_index = m_GameModel->m_actors[i].limbs[j].model_index;			
				
				if (model_index == -1) 
					continue;

				m_GameModel->m_actors[i].SyncModelToActor(j, begin, angle);

				//m_GameModel->SyncModelToActor(i,j, begin, angle, color);			 

				color = m_GameModel->GetColorFromHitpoints(m_GameModel->m_actors[i].limbs[j].Hitpoints, 
														   m_GameModel->m_actors[i].limbs[j].HitpointsMax,
														    m_GameModel->m_actors[i].team);

				m_Graphics->SetModelColor(model_index,color.x,color.y,color.z, 1.0f);
				m_Graphics->SetModelPosition(model_index, begin.x, begin.y, begin.z);				
				m_Graphics->SetModelRotation(model_index, angle.x, angle.y, angle.z);		


			}

		}
	}


	for(int i = 0; i<CORPSE_COUNT;i++)
	{
		if (m_GameModel->m_corpses[i].active)
		{			
			if (!m_GameModel->m_corpses[i].active)
				continue;

			model_index = m_GameModel->m_corpses[i].limb.model_index;			
				
			if (model_index == -1) 
				continue;

			begin = m_GameModel->m_corpses[i].m_position.GetPosition();
			angle = m_GameModel->m_corpses[i].m_position.GetRotation();

			color = m_GameModel->GetColorFromHitpoints(m_GameModel->m_corpses[i].limb.Hitpoints, 
				m_GameModel->m_corpses[i].limb.HitpointsMax,
				m_GameModel->m_corpses[i].team );

			m_Graphics->SetModelColor(model_index,color.x,color.y,color.z, 1.0f);
			m_Graphics->SetModelPosition(model_index, begin.x, begin.y, begin.z);				
			m_Graphics->SetModelRotation(model_index, angle.x, angle.y, angle.z);					

		}
	}
	return true;
}


bool SystemClass::AdvancePositions(float frameTime)
{
	m_Position->SetFrameTime(frameTime);
	m_Position->UpdatePosition();


	int nearest = -1;
	D3DXVECTOR3 new_v,offset;

	for(int i = 0; i<ACTOR_COUNT;i++)
	{
		if (m_GameModel->m_actors[i].active)
		{
			m_GameModel->m_actors[i].m_position.SetFrameTime(frameTime);
			m_GameModel->m_actors[i].m_position.UpdatePosition();
			m_GameModel->m_actors[i].m_position.SetMomentum();

			float ground = m_Graphics->GetTerrainHeight(m_GameModel->m_actors[i].m_position.GetPosX(),m_GameModel->m_actors[i].m_position.GetPosZ());

			m_GameModel->m_actors[i].m_position.UpdateGravity(ground, 6.0f);

			//if (i != Camera_Actor_Index)
//				m_GameModel->UpdateSword(i , 0.0f,0.0f,0.0f,0.0f);

			nearest = m_GameModel->GetActorIndexNearestActor(i);
			if (GeometryClass::Distance(m_GameModel->m_actors[i].m_position.GetPosition(),m_GameModel->m_actors[nearest].m_position.GetPosition()) < 2.0f)
			{
				offset = D3DXVECTOR3(0.0f,0.0f,0.0f);

				if (m_GameModel->m_actors[i].m_position.GetPosition().x > m_GameModel->m_actors[nearest].m_position.GetPosition().x)
					offset.x = 2.1f;
				else
					offset.x = -2.1f;
				if (m_GameModel->m_actors[i].m_position.GetPosition().z > m_GameModel->m_actors[nearest].m_position.GetPosition().z)
					offset.z = 2.1f;
				else
					offset.z = -2.1f;

				new_v = m_GameModel->m_actors[nearest].m_position.GetPosition_V()*0.5 + m_GameModel->m_actors[i].m_position.GetPosition_V()*0.5;

				m_GameModel->m_actors[i].m_position.SetPosition_V(new_v+offset);
				m_GameModel->m_actors[nearest].m_position.SetPosition_V(new_v-offset);
			}




		}
	}

	for(int i = 0; i<CORPSE_COUNT;i++)
	{
		if (m_GameModel->m_corpses[i].active)
		{
			m_GameModel->m_corpses[i].m_position.SetFrameTime(frameTime);			
			m_GameModel->m_corpses[i].m_position.UpdatePosition();

			float ground = m_Graphics->GetTerrainHeight(m_GameModel->m_corpses[i].m_position.GetPosX(),m_GameModel->m_corpses[i].m_position.GetPosZ());
			m_GameModel->m_corpses[i].m_position.UpdateGravity(ground, 2.0f);
		}

	}
	return true;

}


bool SystemClass::SyncCameraAndActor()
{




	if (Camera_Actor_Index == -1)
		return true;

	if (!m_GameModel->m_actors[Camera_Actor_Index].active)
		return false;
	
	float x ,y,z,rx,ry,rz;

	//m_GameModel->m_actors[Camera_Actor_Index].m_position.SetPosition(m_Position->GetPosX(),m_Position->GetPosY(),m_Position->GetPosZ());
	//m_GameModel->m_actors[Camera_Actor_Index].m_position.SetRotation(m_Position->GetPosX(),m_Position->GetPosY(),m_Position->GetPosZ());

		

	x = m_GameModel->m_actors[Camera_Actor_Index].m_position.GetPosX();
	y = m_GameModel->m_actors[Camera_Actor_Index].m_position.GetPosY();
	z = m_GameModel->m_actors[Camera_Actor_Index].m_position.GetPosZ();
	rx = m_GameModel->m_actors[Camera_Actor_Index].m_position.GetRotX() ;
	ry = m_GameModel->m_actors[Camera_Actor_Index].m_position.GetRotY();
	rz = m_GameModel->m_actors[Camera_Actor_Index].m_position.GetRotZ() ;
	


	D3DXVECTOR3 up, position, lookAt;
	float yaw, pitch, roll;
	D3DXMATRIX rotationMatrix;
	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;
	position.x = x;
	position.y = y;
	position.z = z;
	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = -1.0f;
	pitch = 0.2f;
	yaw   = ry + Camera_Actor_Angle;
	roll  = 0;//rz;
	//pitch = rx;
	//yaw   = ry;
	//roll  = rz;
	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);
	D3DXVec3TransformCoord(&lookAt, &lookAt, &rotationMatrix);





	

	x = x - lookAt.x  * Camera_Actor_Distance;
	y = y - lookAt.y * Camera_Actor_Distance;
	z = z - lookAt.z  * Camera_Actor_Distance;
	
	m_Position->SetPosition(x,y,z);
	//m_Position->SetRotation(rx,ry,rz);
	m_Position->SetRotation(pitch,yaw,roll);

	return true;
}


bool SystemClass::CleanUpModels()
{
	for(int i= 0; i<MODEL_LIST_COUNT;i++)
	{
		m_Graphics->DeactivateModel(i);
	}

	for(int i = 0; i<ACTOR_COUNT;i++)
	{
		for(int j = 0;j<LIMB_COUNT;j++)
		{
			if (m_GameModel->m_actors[i].active && m_GameModel->m_actors[i].limbs[j].attached)
			{
				m_Graphics->ActivateModel(m_GameModel->m_actors[i].limbs[j].model_index);
			}
		}
	}

	for(int i = 0 ;i<CORPSE_COUNT;i++)
	{		
		if (m_GameModel->m_corpses[i].active)
		{
			m_Graphics->ActivateModel(m_GameModel->m_corpses[i].limb.model_index);
		}		
	}

	return true;



}












LRESULT CALLBACK SystemClass::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{	
			return DefWindowProc(hwnd, umsg, wparam, lparam);	
}





void SystemClass::InitializeWindows(int& screenWidth, int& screenHeight)
{
	WNDCLASSEX wc;
	DEVMODE dmScreenSettings;
	int posX, posY;


	// Get an external pointer to this object.
	ApplicationHandle = this;

	// Get the instance of this application.
	m_hinstance = GetModuleHandle(NULL);

	// Give the application a name.
	m_applicationName = L"Samurai 2";

	// Setup the windows class with default settings.
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_hinstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_applicationName;
	wc.cbSize = sizeof(WNDCLASSEX);
	
	// Register the window class.
	RegisterClassEx(&wc);

	// Determine the resolution of the clients desktop screen.
	screenWidth  = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	// Setup the screen settings depending on whether it is running in full screen or in windowed mode.
	if(FULL_SCREEN)
	{
		// If full screen set the screen to maximum size of the users desktop and 32bit.
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize       = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth  = (unsigned long)screenWidth;
		dmScreenSettings.dmPelsHeight = (unsigned long)screenHeight;
		dmScreenSettings.dmBitsPerPel = 32;			
		dmScreenSettings.dmFields     = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Change the display settings to full screen.
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// Set the position of the window to the top left corner.
		posX = posY = 0;
	}
	else
	{
		// If windowed then set it to 800x600 resolution.
		screenWidth  = DEFAULT_WINDOW_WIDTH;
		screenHeight = DEFAULT_WINDOW_HEIGHT;

		// Place the window in the middle of the screen.
		//posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth)  / 2;
		//posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight) / 2;
		posX = 0;
		posY = 0;
	}

	// Create the window with the screen settings and get the handle to it.
	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW, m_applicationName, m_applicationName, 
				WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
				posX, posY, screenWidth, screenHeight, NULL, NULL, m_hinstance, NULL);

	// Bring the window up on the screen and set it as main focus.
	ShowWindow(m_hwnd, SW_SHOW);
	SetForegroundWindow(m_hwnd);
	SetFocus(m_hwnd);

	// Hide the mouse cursor.
	ShowCursor(false);

	return;
}



void SystemClass::ShutdownWindows()
{
	// Show the mouse cursor.
	ShowCursor(true);

	// Fix the display settings if leaving full screen mode.
	if(FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}

	// Remove the window.
	DestroyWindow(m_hwnd);
	m_hwnd = NULL;

	// Remove the application instance.
	UnregisterClass(m_applicationName, m_hinstance);
	m_hinstance = NULL;

	// Release the pointer to this class.
	ApplicationHandle = NULL;

	return;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch(umessage)
	{
		// Check if the window is being destroyed.
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}

		// Check if the window is being closed.
		case WM_CLOSE:
		{
			PostQuitMessage(0);		
			return 0;
		}

		// All other messages pass to the message handler in the system class.
		default:
		{
			return ApplicationHandle->MessageHandler(hwnd, umessage, wparam, lparam);
		}
	}
}



