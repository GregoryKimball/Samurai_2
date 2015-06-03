///////////////////////////////////////////////////////////////////////////////
// Filename: modellistclass.cpp
///////////////////////////////////////////////////////////////////////////////
#include "modellistclass.h"

//The class constructor initializes the model information list to null.

ModelListClass::ModelListClass()
{
	m_ModelInfoList = 0;
}


ModelListClass::ModelListClass(const ModelListClass& other)
{
}


ModelListClass::~ModelListClass()
{
}


bool ModelListClass::Initialize(int numModels)
{
	int i;
	float red, green, blue;

	//First store the number of models that will be used and then create the list array of them using the ModelInfoType structure.

	// Store the number of models.
	m_modelCount = numModels;

	// Create a list array of the model information.
	m_ModelInfoList = new ModelInfoType[m_modelCount];
	

	
	if(!m_ModelInfoList)
	{
		return false;
	}

//Seed the random number generator with the current time and then randomly generate the position of color of the models and store them in the list array.

	// Seed the random generator with the current time.
	srand((unsigned int)time(NULL));

	// Go through all the models and randomly generate the model color and position.
	for(i=0; i<m_modelCount; i++)
	{
		// Generate a random color for the model.
		red = (float)rand() / RAND_MAX;
		green = (float)rand() / RAND_MAX;
		blue = (float)rand() / RAND_MAX;

		m_ModelInfoList[i].color = D3DXVECTOR4(red, green, blue, 1.0f);

		// Generate a random position in front of the viewer for the mode.
		m_ModelInfoList[i].positionX = (((float)rand()-(float)rand())/RAND_MAX) * 10.0f + 50.0f;
		m_ModelInfoList[i].positionY = (((float)rand()-(float)rand())/RAND_MAX) * 10.0f + 10.0f;
		m_ModelInfoList[i].positionZ = ((((float)rand()-(float)rand())/RAND_MAX) * 10.0f) + 50.0f;

		m_ModelInfoList[i].rotationX = 0;
		m_ModelInfoList[i].rotationY = 0;
		m_ModelInfoList[i].rotationZ = 0;

		m_ModelInfoList[i].m_Model = new ModelClass();
		m_ModelInfoList[i].active = false;
		m_ModelInfoList[i].actor_index = -1;
		m_ModelInfoList[i].limb_index = -1;

		if(!m_ModelInfoList[i].m_Model)	{		return false;	}


	}

	return true;
}

//The Shutdown function releases the model information list array.

void ModelListClass::Shutdown()
{
	// Release the model information list.
	if(m_ModelInfoList)
	{


		for(int i = 0; i<m_modelCount;i++)
		{
			m_ModelInfoList[i].m_Model->Shutdown();
		}

		delete [] m_ModelInfoList;
		m_ModelInfoList = 0;
	}

	return;
}

//GetModelCount returns the number of models that this class maintains information about.

int ModelListClass::GetModelCount()
{
	return m_modelCount;
}


bool ModelListClass::InitializeModel(int index, ID3D11Device* device, char* modelFilename, WCHAR* textureFilename)
{
	
	bool result;

	result = m_ModelInfoList[index].m_Model->Initialize(device, modelFilename, textureFilename);


	if (result)
	{
		m_ModelInfoList[index].active = true;
	}

	return 	result;

}


int ModelListClass::AddModel(ID3D11Device* device, char* modelFilename, WCHAR* textureFilename)
{


	for (int i =0 ;i<m_modelCount;i++)
	{
		if (!IsActive(i))
		{
			
			InitializeModel(i, device, modelFilename, textureFilename);
			return i;
		}
	}

	return -1;

}



int ModelListClass::AddModel(ID3D11Device* device, ModelClass* model)
{
	
	for (int i =0 ;i<m_modelCount;i++)
	{
		if (!IsActive(i))
		{
			
			m_ModelInfoList[i].m_Model = model;
			m_ModelInfoList[i].active = true;			
			return i;
		}
	}

	return -1;

}



void ModelListClass::RenderModel(int index, ID3D11DeviceContext* device)
{
	m_ModelInfoList[index].m_Model->Render(device);
}

int ModelListClass::GetIndexCount(int index)
{
	return m_ModelInfoList[index].m_Model->GetIndexCount();
}


ID3D11ShaderResourceView* ModelListClass::GetTexture(int index)
{
	return m_ModelInfoList[index].m_Model->GetTexture();
}






//The GetData function extracts the position and color of a sphere at the given input index location.

void ModelListClass::GetData(int index, float& positionX, float& positionY, float& positionZ, D3DXVECTOR4& color)
{
	positionX = m_ModelInfoList[index].positionX;
	positionY = m_ModelInfoList[index].positionY;
	positionZ = m_ModelInfoList[index].positionZ;

	color = m_ModelInfoList[index].color;

	return;
}


void ModelListClass::GetData(int index, float& positionX, float& positionY, float& positionZ, float& rotationX, float& rotationY, float& rotationZ, D3DXVECTOR4& color)
{
	positionX = m_ModelInfoList[index].positionX;
	positionY = m_ModelInfoList[index].positionY;
	positionZ = m_ModelInfoList[index].positionZ;
	rotationX = m_ModelInfoList[index].rotationX;
	rotationY = m_ModelInfoList[index].rotationY;
	rotationZ = m_ModelInfoList[index].rotationZ;

	color = m_ModelInfoList[index].color;

	return;
}



bool ModelListClass::IsActive(int index)
{
	return m_ModelInfoList[index].active;
}

void  ModelListClass::Deactivate(int index)
{
	m_ModelInfoList[index].active = false;

}

void  ModelListClass::Activate(int index)
{
	m_ModelInfoList[index].active = true;

}



void ModelListClass::MoveModelPosition(int index, float positionX, float positionY, float positionZ)
{
	m_ModelInfoList[index].positionX += positionX;
	m_ModelInfoList[index].positionY += positionY;
	m_ModelInfoList[index].positionZ += positionZ;
}





void ModelListClass::MoveModelRotation(int index, float rotationX, float rotationY, float rotationZ)
{
	m_ModelInfoList[index].rotationX += rotationX;
	m_ModelInfoList[index].rotationY += rotationY;
	m_ModelInfoList[index].rotationZ += rotationZ;
}



void ModelListClass::SetModelPosition(int index, float positionX, float positionY, float positionZ)
{
	m_ModelInfoList[index].positionX = positionX;
	m_ModelInfoList[index].positionY = positionY;
	m_ModelInfoList[index].positionZ = positionZ;
}

void ModelListClass::SetModelRotation(int index, float rotationX, float rotationY, float rotationZ)
{
	m_ModelInfoList[index].rotationX = rotationX;
	m_ModelInfoList[index].rotationY = rotationY;
	m_ModelInfoList[index].rotationZ = rotationZ;
}


void ModelListClass::SetModelColor(int index , float r , float g, float b , float alpha)
{

	if (index < 0) 
		return;
	m_ModelInfoList[index].color = D3DXVECTOR4(r,g,b,alpha);

}