#ifndef GJK_ALGORITHM
#define GJK_ALGORITHM

#include "box.h"
//#include <GL/freeglut.h>

	class GJK_Algorithm
	{
	public:
		 GJK_Algorithm();
		~GJK_Algorithm();
		bool CollisionDetection(const Box&, const Box&);
		double ClosestDistance(const Box&, const Box&);
		vector3 point1,point2;
		
	private:
		vector3 a, b, c, d;
		vector3 p1,p2;
		vector<vector3> simplex;

		vector3 ClosestPointToOrigin(vector3&, vector3&, vector3&);
		vector3 ClosestPointToOriginFromLine(vector3&, vector3&);
		vector3 LineNormal(vector3&, vector3&, vector3&);
		vector3 DirectionPointToOrigin(vector3&, vector3&, vector3&);
		vector3  support(Box, Box, const vector3&);
		bool ContainsOrigin(vector3&);
	};


void mouse(int button, int state, int x, int y);
void key(int key, int x, int y);
void motion(int x, int y);
void renderScene1(void);
void reshape (int w, int h);



#endif