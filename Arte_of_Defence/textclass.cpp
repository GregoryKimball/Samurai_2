///////////////////////////////////////////////////////////////////////////////
// Filename: textclass.cpp
///////////////////////////////////////////////////////////////////////////////
#include "textclass.h"
#include <string>


TextClass::TextClass()
{
	m_Font = 0;
	m_FontShader = 0;

	/*
	m_sentence1 = 0;
	m_sentence2 = 0;
	
	m_sentence3 = 0;
	m_sentence4 = 0;*/
}


TextClass::TextClass(const TextClass& other)
{
}


TextClass::~TextClass()
{
}


string TextClass::debug_strings[MESSAGE_COUNT] = {};

TextClass::MessageType TextClass::HUD_strings[HUD_COUNT] = {};


bool TextClass::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, HWND hwnd, int screenWidth, int screenHeight, 
						   D3DXMATRIX baseViewMatrix)
{
	bool result;



	// Store the screen width and height.
	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	// Store the base view matrix.
	m_baseViewMatrix = baseViewMatrix;



	// Create the font object.
	m_Font = new FontClass;
	if(!m_Font)
	{
		return false;
	}

	// Initialize the font object.
	result = m_Font->Initialize(device, "../Arte_of_Defence/fonts/font_index4.txt", L"../Arte_of_Defence/fonts/font.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the font object.", L"Error", MB_OK);
		return false;
	}



	// Create the font shader object.
	m_FontShader = new FontShaderClass;
	if(!m_FontShader)
	{
		return false;
	}

	// Initialize the font shader object.
	result = m_FontShader->Initialize(device, hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the font shader object.", L"Error", MB_OK);
		return false;
	}


	for(int i =0;i<MESSAGE_COUNT;i++)
	{
		TextClass::debug_strings[i] = "";		
		result = InitializeSentence(&debug_sentences[i],MESSAGE_LENGTH,device);
		if(!result)
			return false;
	}



	for(int i =0;i<HUD_COUNT;i++)
	{

		D3DXVECTOR3 c = *new D3DXVECTOR3(1.0f,1.0f,1.0f);
		D3DXVECTOR2 p = *new D3DXVECTOR2(1.0f,1.0f);

		SetMessageType("",p,c,&TextClass::HUD_strings[i]);


		result = InitializeSentence(&HUD_sentences[i],HUD_LENGTH,device);

		if(!result)
			return false;
	}


	return true;
}




void TextClass::Shutdown()
{
	for(int i =0;i<MESSAGE_COUNT;i++)
	{
		ReleaseSentence(&debug_sentences[i]);
	}
	for(int i =0;i<HUD_COUNT;i++)
	{
		ReleaseSentence(&HUD_sentences[i]);
	}

	

	// Release the font shader object.
	if(m_FontShader)
	{
		m_FontShader->Shutdown();
		delete m_FontShader;
		m_FontShader = 0;
	}

	// Release the font object.
	if(m_Font)
	{
		m_Font->Shutdown();
		delete m_Font;
		m_Font = 0;
	}

	return;
}



bool TextClass::Render(ID3D11DeviceContext* deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX orthoMatrix)
{
	bool result;

	
	for(int i =0;i<MESSAGE_COUNT;i++)
	{
		if (TextClass::debug_strings[i].length() == 0)
			continue;

		result = UpdateSentence(debug_sentences[i],TextClass::debug_strings[i],600,i*15+15,1.0f,1.0f,1.0f,deviceContext);
		if(!result)		return false;
		result = RenderSentence(deviceContext, debug_sentences[i], worldMatrix, orthoMatrix);
		if(!result)		return false;
	}
	
	for(int i =0;i<HUD_COUNT;i++)
	{
		if (TextClass::HUD_strings[i].message.length() == 0)
			continue;
		
		SentenceType * t = HUD_sentences[i];
		MessageType m = TextClass::HUD_strings[i];


		result = UpdateSentence(HUD_sentences[i],m.message,(int)m.position.x,(int)m.position.y,m.color.x,m.color.y,m.color.z,deviceContext);
		if(!result)		return false;
		result = RenderSentence(deviceContext, HUD_sentences[i], worldMatrix, orthoMatrix);
		if(!result)		return false;

	}



	return true;
}



bool TextClass::InitializeSentence(SentenceType** sentence, int maxLength, ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	int i;


	// Create a new sentence object.
	*sentence = new SentenceType;
	if(!*sentence)
	{
		return false;
	}

	// Initialize the sentence buffers to null.
	(*sentence)->vertexBuffer = 0;
	(*sentence)->indexBuffer = 0;

	// Set the maximum length of the sentence.
	(*sentence)->maxLength = maxLength;

	// Set the number of vertices in the vertex array.
	(*sentence)->vertexCount = 6 * maxLength;

	// Set the number of indexes in the index array.
	(*sentence)->indexCount = (*sentence)->vertexCount;

	// Create the vertex array.
	vertices = new VertexType[(*sentence)->vertexCount];
	if(!vertices)
	{
		return false;
	}

	// Create the index array.
	indices = new unsigned long[(*sentence)->indexCount];
	if(!indices)
	{
		return false;
	}

	// Initialize vertex array to zeros at first.
	memset(vertices, 0, (sizeof(VertexType) * (*sentence)->vertexCount));

	// Initialize the index array.
	for(i=0; i<(*sentence)->indexCount; i++)
	{
		indices[i] = i;
	}



	// Set up the description of the dynamic vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * (*sentence)->vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &(*sentence)->vertexBuffer);
	if(FAILED(result))
	{
		return false;
	}


	// Set up the description of the static index buffer.
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * (*sentence)->indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &(*sentence)->indexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Release the vertex array as it is no longer needed.
	delete [] vertices;
	vertices = 0;

	// Release the index array as it is no longer needed.
	delete [] indices;
	indices = 0;

	return true;
}



bool TextClass::UpdateSentence(SentenceType* sentence, string text, int positionX, int positionY, float red, float green, float blue,
			       ID3D11DeviceContext* deviceContext)
{
	int numLetters;
	VertexType* vertices;
	float drawX, drawY;
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	VertexType* verticesPtr;



	// Store the color of the sentence.
	sentence->red = red;
	sentence->green = green;
	sentence->blue = blue;

	// Get the number of letters in the sentence.
	numLetters = text.length();

	// Check for possible buffer overflow.
	if(numLetters > sentence->maxLength)
	{
		return false;
	}

	// Create the vertex array.
	vertices = new VertexType[sentence->vertexCount];
	if(!vertices)
	{
		return false;
	}

	// Initialize vertex array to zeros at first.
	memset(vertices, 0, (sizeof(VertexType) * sentence->vertexCount));



	// Calculate the X and Y pixel position on the screen to start drawing to.
	drawX = (float)(((m_screenWidth / 2) * -1) + positionX);
	drawY = (float)((m_screenHeight / 2) - positionY);



	// Use the font class to build the vertex array from the sentence text and sentence draw location.
	m_Font->BuildVertexArray((void*)vertices, text, drawX, drawY);



	// Lock the vertex buffer so it can be written to.
	result = deviceContext->Map(sentence->vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if(FAILED(result))
	{
		return false;
	}

	// Get a pointer to the data in the vertex buffer.
	verticesPtr = (VertexType*)mappedResource.pData;

	// Copy the data into the vertex buffer.
	memcpy(verticesPtr, (void*)vertices, (sizeof(VertexType) * sentence->vertexCount));

	// Unlock the vertex buffer.
	deviceContext->Unmap(sentence->vertexBuffer, 0);

	// Release the vertex array as it is no longer needed.
	delete [] vertices;
	vertices = 0;

	return true;
}


void TextClass::ReleaseSentence(SentenceType** sentence)
{
	if(*sentence)
	{
		// Release the sentence vertex buffer.
		if((*sentence)->vertexBuffer)
		{
			(*sentence)->vertexBuffer->Release();
			(*sentence)->vertexBuffer = 0;
		}

		// Release the sentence index buffer.
		if((*sentence)->indexBuffer)
		{
			(*sentence)->indexBuffer->Release();
			(*sentence)->indexBuffer = 0;
		}

		// Release the sentence.
		delete *sentence;
		*sentence = 0;
	}

	return;
}



bool TextClass::RenderSentence(ID3D11DeviceContext* deviceContext, SentenceType* sentence, D3DXMATRIX worldMatrix, 
			       D3DXMATRIX orthoMatrix)
{
	unsigned int stride, offset;
	D3DXVECTOR4 pixelColor;
	bool result;

	
	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType); 
	offset = 0;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &sentence->vertexBuffer, &stride, &offset);

	// Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(sentence->indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// Create a pixel color vector with the input sentence color.
	pixelColor = D3DXVECTOR4(sentence->red, sentence->green, sentence->blue, 1.0f);

	// Render the text using the font shader.
	result = m_FontShader->Render(deviceContext, sentence->indexCount, worldMatrix, m_baseViewMatrix, orthoMatrix, m_Font->GetTexture(), 
				      pixelColor);
	if(!result)
	{
		false;
	}

	return true;
}





bool TextClass::SetAccelerometer(int x, int y, int z,  ID3D11DeviceContext* deviceContext)
{
	
	
	string message = " X: " + GetString( x) +  " Y: " + GetString( y) +  " Z: " + GetString( z);
	D3DXVECTOR2 position = *new D3DXVECTOR2(200,60);
	D3DXVECTOR3 color = *new D3DXVECTOR3(0.0f,1.0f,0.0f);	

	SetMessageType(message , position , color, &HUD_strings[0]);
	
	return true;

}


bool TextClass::SetFps(int fps, ID3D11DeviceContext* deviceContext)
{

	if(fps > 9999)
	{
		fps = 9999;
	}

	float red, green, blue;
	if(fps >= 60)
	{
		red = 0.0f;		green = 1.0f;		blue = 0.0f;
	}
	if(fps < 60)
	{
		red = 1.0f;		green = 1.0f;		blue = 0.0f;
	}
	if(fps < 30)
	{
		red = 1.0f;		green = 0.0f;		blue = 0.0f;
	}



	string message = " Fps: " + GetString(fps);
	D3DXVECTOR2 position = *new D3DXVECTOR2(20,60);
	D3DXVECTOR3 color = *new D3DXVECTOR3(red,green,blue);	

	SetMessageType(message , position , color, &HUD_strings[1]);


	return true;
}


bool TextClass::SetCpu(int cpu, ID3D11DeviceContext* deviceContext)
{


	string message = " Cpu: " + to_string((double long) cpu);
	D3DXVECTOR2 position = *new D3DXVECTOR2(20,80);
	D3DXVECTOR3 color = *new D3DXVECTOR3(0.0f,1.0f,0.0f);	

	SetMessageType(message , position , color, &HUD_strings[2]);
	
	

	
	return true;
}



bool TextClass::SetCameraPosition(float camX,float camY, float camZ, float rx, float ry, float rz, ID3D11DeviceContext* deviceContext)
{
	


	float deg = 57.29577951f;


	string message = " X: " + GetString((int) camX) + " Y: " + GetString( (int)camY) +  " Z: " + GetString( (int) camZ);
	D3DXVECTOR2 position = *new D3DXVECTOR2(20,180);
	D3DXVECTOR3 color = *new D3DXVECTOR3(1.0f,1.0f,0.0f);	
	SetMessageType(message , position , color, &HUD_strings[3]);


	message = " RX: " + GetString(rx*deg,2) + " RY: " + GetString(ry*deg,2) + " RZ: " + GetString(rz*deg,2);
	 position = *new D3DXVECTOR2(20,220);
	 color = *new D3DXVECTOR3(1.0f,0.0f,1.0f);	
	 SetMessageType(message , position , color, &HUD_strings[4]);

	return true;
}








bool TextClass::SetMousePosition(int mouseX, int mouseY, ID3D11DeviceContext* deviceContext)
{

	

	string message = " Mouse X: " + to_string((double long) mouseX) ;
	D3DXVECTOR2 position = *new D3DXVECTOR2(20,20);
	D3DXVECTOR3 color = *new D3DXVECTOR3(1.0f,1.0f,1.0f);	

	SetMessageType(message , position , color, &HUD_strings[5]);


	message = " Mouse Y: " + to_string((double long) mouseY);
	 position = *new D3DXVECTOR2(20,40);
	 color = *new D3DXVECTOR3(1.0f,1.0f,1.0f);	

	SetMessageType(message , position , color, &HUD_strings[6]);
	return true;
}




bool TextClass::SetRenderCount(int rc, ID3D11DeviceContext* deviceContext)
{

	string message = " Render Count:  " + GetString(rc) ;
	D3DXVECTOR2 position = *new D3DXVECTOR2(20,100);
	D3DXVECTOR3 color = *new D3DXVECTOR3(0.0f,1.0f,0.0f);	

	SetMessageType(message , position , color, &HUD_strings[7]);


	return true;
}





string TextClass::GetString(int i )
{
	return to_string((long double) i);
}




string TextClass::GetString(float n, int p)
{

	float m = n * (float) pow((double)10,(double)p);
	int o = (int) m;
	float q = ((float) o) /  (float) pow((double)10,(double)p);


	return  to_string((long double)q );
}


string TextClass::GetString(D3DXVECTOR3 v, int p)
{
	return 
		"    X:   " + GetString( v.x,p) + 
		"    Y:   " + GetString( v.y,p) + 
		"    Z:   " + GetString( v.z,p)  ;
}


void TextClass::SetMessageType(string m, D3DXVECTOR2 position, D3DXVECTOR3 color, MessageType * mt)
{

	mt->color.x = color.x;
	mt->color.y = color.y;
	mt->color.z = color.z;

	mt->message = m;

	mt->position.x = position.x;
	mt->position.y = position.y;

}