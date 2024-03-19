#ifndef Box_H
#define Box_H

#include "MathOp.h"
#include "dependente\glew\glew.h"
#include "dependente\glm\glm.hpp"
#include "vector.h"
#include "VertexFormat.h"
#include <iostream>
#include <vector>
using namespace std;

class Box
{
public:
	Box(void);
	~Box(){}

	
	float mass, invMass;
	
	glm::mat4 modelMatrix;
	
	std::vector<vector3> vertices;


		
	void Set(const Vec2& w, const vector3& position, float m);
		
	void setVertices(std::vector<vector3>);

	//used for gjk
	vector3 getFarthestPointInDirection(const vector3&);

	void positionUpdate(const vector3&);
	
	vector3 getPosition();

	//used for aabb test
	vector3 max;
	vector3 min;


	
};



#endif