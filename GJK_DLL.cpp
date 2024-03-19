#define EXPORTBUILD
#include "GJK_DLL.h"
#include "box.h"
#include "GJK_Algorithm.h"

GJK_DLL::GJK_DLL(void)  
{
}

GJK_DLL::~GJK_DLL(void)  
{
}

float GJK( float Object_A[][3], float Object_B[][3], int Length_A, int Length_B, float ClosestPoint1[3], float ClosestPoint2[3])
{
	Box box1,box2;
	vector3 point;
	GJK_Algorithm gjk;
	float ClosestDistance;
	for(int i=0;i<Length_A;i++)
	{
		point.x=Object_A[i][0];
		point.y=Object_A[i][1];
		point.z=Object_A[i][2];
		box1.vertices.push_back(point);
	}
	for(int i=0;i<Length_B;i++)
	{
		point.x=Object_B[i][0];
		point.y=Object_B[i][1];
		point.z=Object_B[i][2];
		box2.vertices.push_back(point);
	}
	
	if(gjk.CollisionDetection(box1,box2))
		return -1;

	ClosestDistance=gjk.ClosestDistance(box1,box2);
	ClosestPoint1[0]=gjk.point1.x;
	ClosestPoint1[1]=gjk.point1.y;
	ClosestPoint1[2]=gjk.point1.z;
	ClosestPoint2[0]=gjk.point2.x;
	ClosestPoint2[1]=gjk.point2.y;
	ClosestPoint2[2]=gjk.point2.z;
	return ClosestDistance;
}