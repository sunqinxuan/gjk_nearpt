#ifndef PHYSICS_H
#define PHYSICS

#pragma once
#include "GJK_Algorithm.h"
#include "Collision.h"


//To be implemented
class Physics{

public:
	std::vector<Box> rigidBodies;
	
	Collision* collision;

	

	inline void Add(Box box)
	{
		rigidBodies.push_back(box);
	}

	inline void Clear()
	{
		rigidBodies.clear();
	}
 
	Physics(void);
	~Physics(void);
	void Step(float dt);
	

private:

	GJK_Algorithm gjk_algorithm;
	void BroadPhase();
	int collisionNumber;//display only
};

Physics::~Physics()
{
	delete(collision);
}
Physics::Physics()
{
	collision = new Collision();
}
void Physics::Step(float dt)
{
	float inv_dt = dt > 0.0f ? 1.0f / dt : 0.0f;

	BroadPhase();

}
void Physics::BroadPhase()
{
	
	for (int i = 0; i < rigidBodies.size(); ++i)
	{
		Box bi = rigidBodies[i];
	
		for (int j = i + 1; j < rigidBodies.size(); ++j)
		{
			Box bj = rigidBodies[j];

			if (bi.invMass == 0.0f || bj.invMass == 0.0f)//skip table(big box) test
				continue;
			
			collision->SetMaxMin(bi);
			collision->SetMaxMin(bj);

			bool c = collision->TestAABBAABB(bi, bj);
		
			if (c)//if AABB test is ok
			{
				 bool gjk=	gjk_algorithm.CollisionDetection(bi, bj);
				 if (gjk)
				 {
					 printf("\n Collision detected %d \n",collisionNumber++);

				 }
				 else
				 {
					 collisionNumber = 0;
				 }
			}

		}
	}
}

#endif