#ifndef _GEOMETRYCLASS_H_
#define _GEOMETRYCLASS_H_


#include <d3d11.h>
#include <d3dx10math.h>
//#include <math.h>

class GeometryClass
{
public:

	static float GeometryClass::ClosestDistance(D3DXVECTOR3 , D3DXVECTOR3 , D3DXVECTOR3 , D3DXVECTOR3 );	
	static 	D3DXVECTOR3 GeometryClass::GetEnd(D3DXVECTOR3 , D3DXVECTOR3, float );
	static 	D3DXVECTOR3 GeometryClass::GetAngle(D3DXVECTOR3 , D3DXVECTOR3,D3DXVECTOR3,D3DXVECTOR3);
	static float GeometryClass::Distance(D3DXVECTOR3 , D3DXVECTOR3);
	static float GeometryClass::Abs(float);
	static float GeometryClass::GetYAngle(D3DXVECTOR3 , D3DXVECTOR3);
	 static float GeometryClass::NormalizeAngle(float , float );
private:


	static void GeometryClass::LineCollide3D(D3DXVECTOR3 , D3DXVECTOR3 , D3DXVECTOR3 , D3DXVECTOR3 , D3DXVECTOR3& , D3DXVECTOR3& );	
	static float GeometryClass::GetDmnop(D3DXVECTOR3* , int , int , int , int );
	


};

#endif
