////////////////////////////////////////////////////////////////////////////////
// Filename: textclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _TEXTCLASS_H_
#define _TEXTCLASS_H_

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "fontclass.h"
#include "fontshaderclass.h"


const int HUD_COUNT = 20;
const int HUD_LENGTH = 64;

const int MESSAGE_COUNT = 20;
const int MESSAGE_LENGTH = 128;

////////////////////////////////////////////////////////////////////////////////
// Class name: TextClass
////////////////////////////////////////////////////////////////////////////////
class TextClass
{
private:




	
	struct SentenceType
	{
		ID3D11Buffer *vertexBuffer, *indexBuffer;
		int vertexCount, indexCount, maxLength;
		float red, green, blue;
	};



	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};

public:

	struct MessageType
	{
		D3DXVECTOR3 color;
		D3DXVECTOR2 position;
		string message;
	};

	TextClass();
	TextClass(const TextClass&);
	~TextClass();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, HWND, int, int, D3DXMATRIX);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX);

	bool SetMousePosition(int, int, ID3D11DeviceContext*);

	bool SetFps(int,ID3D11DeviceContext*);
	bool SetCpu(int,ID3D11DeviceContext*);
	bool SetAccelerometer(int, int, int, ID3D11DeviceContext*);
	bool SetRenderCount(int, ID3D11DeviceContext*);
	bool SetCameraPosition(float ,float ,float , float,float,float, ID3D11DeviceContext* );


	static string TextClass::GetString(int);
	static string TextClass::GetString(float,int);
	static string TextClass::GetString(D3DXVECTOR3,int);

	static string TextClass::debug_strings[MESSAGE_COUNT];
	static MessageType TextClass::HUD_strings[HUD_COUNT];
	
	


private:
	bool InitializeSentence(SentenceType**, int, ID3D11Device*);
	bool UpdateSentence(SentenceType*, string, int, int, float, float, float, ID3D11DeviceContext*);
	void ReleaseSentence(SentenceType**);
	bool RenderSentence(ID3D11DeviceContext*, SentenceType*, D3DXMATRIX, D3DXMATRIX);
	void TextClass::SetMessageType(string , D3DXVECTOR2 , D3DXVECTOR3 , TextClass::MessageType*);
	
private:
	FontClass* m_Font;
	FontShaderClass* m_FontShader;
	int m_screenWidth, m_screenHeight;
	D3DXMATRIX m_baseViewMatrix;


	SentenceType* debug_sentences[MESSAGE_COUNT];
	SentenceType* HUD_sentences[HUD_COUNT];

	/*
	SentenceType* m_sentence1;
	SentenceType* m_sentence2;
	SentenceType* m_sentence3;
	SentenceType* m_sentence4;
	SentenceType* m_sentence_fps;
	SentenceType* m_sentence_cpu;
	SentenceType* m_sentence_render_count;
	SentenceType* m_sentence_position;
	SentenceType* m_sentence_rotation;

	SentenceType* m_sentence_accelerometer;

	SentenceType* m_sentence_debug;*/

};

#endif
