#include "box.h"

Box::Box()
{

}

void Box::Set(const Vec2& pWidth, const vector3& pos, float m)
{
	
	
	modelMatrix = glm::mat4(pWidth.x, 0, 0, 0, 0, pWidth.y, 0, 0, 0, 0, pWidth.x, 0, pos.x, pos.y, pos.z, 1);
	
	mass = m;

	if (mass < FLT_MAX)
	{
		invMass = 1.0f / mass;
	}
	else
	{
		invMass = 0.0f;
		
	}
}



void Box::positionUpdate(const vector3& vector)
{
	modelMatrix[3][0] += vector.x;
	modelMatrix[3][1] += vector.y;
	modelMatrix[3][2] += vector.z;

	
}

vector3 Box::getPosition()
{
	return vector3(modelMatrix[3][0], modelMatrix[3][1], modelMatrix[3][2]);
}

void Box::setVertices(std::vector<vector3> vertices)
{
	max.x = vertices[0].x;
	max.y = vertices[1].y;
	max.z = vertices[2].z;

	min.x = vertices[0].x;
	min.y = vertices[1].y;
	min.z = vertices[2].z;


	for (int i = 0; i < vertices.size(); i++)
	{
		this->vertices.push_back(vector3(vertices[i].x, vertices[i].y, vertices[i].z));
	
		//add20 offset to test GJK; must be removed
		if (vertices[i].x > max.x) max.x = vertices[i].x+20;
		if (vertices[i].y > max.y) max.y = vertices[i].y+20;
		if (vertices[i].z > max.z) max.z = vertices[i].z+20;
														
		if (vertices[i].x < min.x) min.x = vertices[i].x-20;
		if (vertices[i].y < min.y) min.y = vertices[i].y-20;
		if (vertices[i].z < min.z) min.z = vertices[i].z-20;
	
	}



}

vector3 Box::getFarthestPointInDirection(const vector3& dir)
{

	vector3 returnVector;

	//convert in world coordinates
	glm::vec4  m = modelMatrix * glm::vec4(vertices[0].x, vertices[0].y, vertices[0].z, 1);
	vector3 worldVertex = vector3(m.x, m.y, m.z);

	float maxDot = worldVertex.dot(dir);
	returnVector = worldVertex;

	for (int i = 1; i < vertices.size(); i++)
	{
		//convert in world coordinates
		m = modelMatrix * glm::vec4(vertices[i].x, vertices[i].y, vertices[i].z, 1);
		worldVertex = vector3(m.x, m.y, m.z);

		float dot = worldVertex.dot(dir);

		//find biggest dot product
		if (dot > maxDot)
		{
			maxDot = dot;
			returnVector = worldVertex;

		}

	}

	return returnVector;
}
