#ifndef COLLISION_H
#define COLLISION_H
#pragma once

class Collision
{
	public:
		Collision(){  };
		Collision(const Collision&){};
		~Collision(){};

		bool SphereCollision(vector3 pos1,float radius,vector3 pos2, float radius2);
		void SetMaxMin(Box& a);
		bool TestAABBAABB(const Box& a,const Box& b);

	
};

bool Collision::SphereCollision(vector3 pos1, float r1, vector3 pos2, float r2)
{
	
   //compute distance
	vector3 relativePos = pos2 - pos1;
	float distance = relativePos.x*relativePos.x + relativePos.y*relativePos.y + relativePos.z*relativePos.z;

	float minDistance = r1 + r2;

	return distance <=minDistance*minDistance;

   

}

bool Collision:: TestAABBAABB(const Box& a,const Box& b)
{
	// Exit with no intersection if separated along an axis
	if (a.max.x < b.min.x || a.min.x > b.max.x) return 0;
	if (a.max.y < b.min.y || a.min.y > b.max.y) return 0;
	if (a.max.z < b.min.z || a.min.z > b.max.z) return 0;
	// Overlapping on all axes means AABBs are intersecting
	return 1;
}

void Collision::SetMaxMin(Box& a)
{
	glm::vec4 vmax = a.modelMatrix*glm::vec4(a.max.x, a.max.y, a.max.z, 1);

	a.max = vector3(vmax.x,vmax.y,vmax.z);

	glm::vec4 vmin = a.modelMatrix*glm::vec4(a.min.x, a.min.y, a.min.z, 1);

	a.min = vector3(vmin.x, vmin.y, vmin.z);
}

#endif