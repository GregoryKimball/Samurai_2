
#include "GeometryClass.h"






 float GeometryClass::ClosestDistance(D3DXVECTOR3 p1, D3DXVECTOR3 p2, D3DXVECTOR3 p3, D3DXVECTOR3 p4)
{
	D3DXVECTOR3 pa, pb;

	LineCollide3D(p1, p2, p3, p4, pa, pb);

	float d=Distance(pa, pb);
		
		return d;
}

 float GeometryClass::Distance(D3DXVECTOR3 p1, D3DXVECTOR3  p2)
{
	
	return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y) + (p1.z - p2.z)*(p1.z - p2.z));
}


 void GeometryClass::LineCollide3D(D3DXVECTOR3 p1, D3DXVECTOR3 p2, D3DXVECTOR3 p3, D3DXVECTOR3 p4, D3DXVECTOR3  &pa, D3DXVECTOR3 &pb)
{

	D3DXVECTOR3* l = new D3DXVECTOR3[4];

	l[0] = p1;
	l[1] = p2;
	l[2] = p3;
	l[3] = p4;
	
	float d1343 = GetDmnop(l,1,3,4,3);
	float d4321 = GetDmnop(l,4,3,2,1);
	float d4343 = GetDmnop(l,4,3,4,3);

	float d1321 = GetDmnop(l,1,3,2,1);
	float d2121 = GetDmnop(l,2,1,2,1);
	

	float mua = (d1343 * d4321 - d1321 * d4343) / 
				(d2121 * d4343 - d4321 * d4321);

	float mub = (d1343 + mua * d4321)/d4343;


	if (mua < 0.0f) mua = 0.0f;
	if (mua > 1.0f) mua = 1.0f;

	if (mub < 0.0f) mub = 0.0f;
	if (mub > 1.0f) mub = 1.0f;

	pa.x = p1.x + mua * (p2.x - p1.x);
	pa.y = p1.y + mua * (p2.y - p1.y);
	pa.z = p1.z + mua * (p2.z - p1.z);

	pb.x = p3.x + mub * (p4.x - p3.x);
	pb.y = p3.y + mub * (p4.y - p3.y);
	pb.z = p3.z + mub * (p4.z - p3.z);

	

	//mub = 0.0f;

}

 D3DXVECTOR3 GeometryClass::GetEnd(D3DXVECTOR3 begin, D3DXVECTOR3 angle, float length)
{
	D3DXVECTOR3 end;

	end.x = (float) sinf(angle.y)*cosf(angle.x)* length + begin.x;
	end.y = (float) -1 * sinf(angle.x)* length + begin.y;
	end.z = (float) cosf(angle.y)*cosf(angle.x)*length + begin.z;

	return end;
}




D3DXVECTOR3 GeometryClass::GetAngle(D3DXVECTOR3 begin, D3DXVECTOR3 end,  D3DXVECTOR3 facing, D3DXVECTOR3 base_limb)
{
	D3DXVECTOR3 diff = end - begin;
	D3DXVECTOR3 angle;
	D3DXVECTOR3 diff_roll; 

	
	float xyz_len = sqrt(diff.x *diff.x + diff.y * diff.y + diff.z * diff.z);
	
	diff = diff/xyz_len;

	float xz_len = sqrt(diff.x *diff.x + diff.z * diff.z);
	float xy_len = sqrt(diff.x *diff.x + diff.y * diff.y);


	//float diff_roll.x = diff.x * sinf(facing.z)*cosf(facing.y) + diff.y * cosf(facing.z)*sinf(facing.y);
	//float diff_roll.y = diff.x * sinf(facing.z) + diff.y * cosf(facing.z);
	//float diff_roll.z = 0.0f;


	/*
	angle.x = acosf(diff.y/1.0f)-acosf(0.0f);
	angle.y = -1 * atan2f(diff.z,diff.x)+acosf(0.0f);
	//angle.z =	angle.y - facing.y;
	//angle.z =	angle.y - facing.y + facing.x * sinf(base_limb.y) * cosf(base_limb.x);

	*/


	
	angle.x = acosf(diff.y/1.0f)-acosf(0.0f);
	//angle.y = -1 * atan2f(diff.z,diff.x)+acosf(0.0f);
	angle.y = -1 * atan2f(diff.z,diff.x)+acosf(0.0f);;
	


	if (angle.y < 0.0f)
		angle.y += 2.0f * 3.1415926f;

	if (angle.y > 2.0f * 3.1415926f)
		angle.y -= 2.0f * 3.1415926f;

	//angle.z =	angle.y - facing.y;
	//angle.z =	angle.y - facing.y + facing.x * sinf(base_limb.y);
	//angle.z =	angle.y - facing.y + facing.x * sinf(base_limb.y) - angle.y * sinf(base_limb.y)* cosf(base_limb.y) ;
	angle.z =	angle.y - facing.y + facing.x * sinf(base_limb.y) * cosf(base_limb.x);

	//if (sinf(base_limb.y)* sinf(base_limb.x) != 0.0f)
		//angle.z=0.0f;


	angle.z += base_limb.z;

	if (angle.z < 0.0f)
		angle.z += 2.0f * 3.1415926f;

	if (angle.z > 2.0f * 3.1415926f)
		angle.z -= 2.0f * 3.1415926f;



	

	
	


	return angle;
}



 float GeometryClass::GetDmnop(D3DXVECTOR3* l, int m, int n, int o, int p)
{

	return (l[m-1].x - l[n-1].x)*(l[o-1].x - l[p-1].x) + (l[m-1].y - l[n-1].y) * (l[o-1].y - l[p-1].y) + (l[m-1].z - l[n-1].z) * (l[o-1].z - l[p-1].z);
	
}


 float GeometryClass::GetYAngle(D3DXVECTOR3 me, D3DXVECTOR3 you)
 {
	 
	 float dx = me.x - you.x;
	 float dz = me.z - you.z;
	 float a = -1.0f * atan2f(dz,dx)+ 1.57079632675f + 3.1415936f;
	 return a;
 }

 float GeometryClass::NormalizeAngle(float m_angle, float boundary_plusminus)
 {
	 float a = m_angle;
	 if (a> boundary_plusminus)
		 a-= boundary_plusminus * 2;
	 if (a< -1.0f*boundary_plusminus)
		 a+= boundary_plusminus * 2;
	 return a;
 }