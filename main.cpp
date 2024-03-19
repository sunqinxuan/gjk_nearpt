#include <iostream>
#include "box.h"
#include "GJK_Algorithm.h"
#include <GL/freeglut.h>
#include <time.h>
//#include "dependente\freeglut\freeglut.h"
using namespace std;
#define SIGN(x) ( (x)<0 ? -1:((x)>0?1:0 ) )
#define CV_PI 3.1415926
#define N 50

float xyzdata[480][640][3];
float texture[480][640][3];
int glWinWidth = 640, glWinHeight = 480;
double eyex, eyey, eyez, atx, aty, atz;
double sx=1,sy=1,sz=1;
bool leftClickHold = false, rightClickHold = false;
int mx,my;  
int ry = 90, rx = 90;
double mindepth=200.0, maxdepth=2000.0;
double radius = 3000.0;

Box box1;
Box box2;
vector3 point1,point2;
vector<vector3> mink;
vector3 point;
GJK_Algorithm gjk;
//bool flag=0;


void mouse(int button, int state, int x, int y)
{
   if(button == GLUT_LEFT_BUTTON)
   {
      if(state == GLUT_DOWN)
      {
         leftClickHold=true;
      }
      else
      {
         leftClickHold=false;
      }
   }

   if (button== GLUT_RIGHT_BUTTON)
   {
      if(state == GLUT_DOWN)
      {
         rightClickHold=true;
      }
      else
      {
         rightClickHold=false;
      }
   }
}

void key(int key, int x, int y)
{
	switch(key)
	{
	case GLUT_KEY_UP:
		sx+=0.1;
		sy+=0.1;
		sz+=0.1;
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		sx-=0.1;
		sy-=0.1;
		sz-=0.1;
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:
		gjk.flag=true;
		break;
	default:
		sx=sx;
		sy=sy;
		sz=sz;
	}
}

void motion(int x, int y)
{
   int rstep = 5; 
   if(leftClickHold==true)
   {
      if( abs(x-mx) > abs(y-my) )
      {
         rx += SIGN(x-mx)*rstep;    
      }
      else
      {
         ry -= SIGN(y-my)*rstep;    
      }
      
      mx=x;
      my=y;
      glutPostRedisplay();
   }

   if(rightClickHold==true)
   {
      radius += SIGN(y-my)*100.0;
      radius = max( radius, 100.0 );
      mx=x;
      my=y;
      glutPostRedisplay();
   }
}

void renderScene1(void) 
{
   // clear screen and depth buffer
   glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
   // Reset the coordinate system before modifying 
   glLoadIdentity();   
   // set the camera position
   atx = 0.0f;
   aty = 0.0f;
   atz = ( mindepth - maxdepth ) / 2.0f;
   eyex = atx + radius * sin( CV_PI * ry / 180.0f ) * cos( CV_PI * rx/ 180.0f ); 
   eyey = aty + radius * cos( CV_PI * ry/ 180.0f ); 
   eyez = atz + radius * sin( CV_PI * ry / 180.0f ) * sin( CV_PI * rx/ 180.0f );
   gluLookAt ( eyex, eyey, eyez, atx, aty, atz,0.0, -1.0, 0.0);
   //gluLookAt(0.0f,0.0f,6000.0f,0.0f,0.0f,1000.0f,0.0,1.0,0.0);
   glRotatef(0,0,1,0);
   glRotatef(-180,1,0,0);
   glScalef(sx,sy,sz);

   glPointSize(2.0); 

   glBegin(GL_LINES);
   glColor3f(1,0,0);
   glVertex3f(0,0,0);
   //z:b
   //glColor3f(0,0,1);
   //glVertex3f(0,0,100);
   //glColor3f(0,0,1);
   //glVertex3f(0,0,500);
   //glColor3f(0,0,1);
   glVertex3f(0,0,1000);
   //x:r
   //glColor3f(1,0,0);
   glVertex3f(0,0,0);
   //glColor3f(1,0,0);
   //glVertex3f(500,0,0);
   //glColor3f(1,0,0);
   glVertex3f(1000,0,0);
   //y:g
   //glColor3f(0,1,0);
   glVertex3f(0,0,0);
   //glColor3f(0,1,0);
   //glVertex3f(0,500,0);
   //glColor3f(0,1,0);
   glVertex3f(0,1000,0);
   glEnd(); 

	//glBegin(GL_POLYGON);
	//glColor3f(1,0,0);
	//for(vector<vector3>::iterator it=box1.vertices.begin();it!=box1.vertices.end();++it)
	//{
	//	glVertex2f(it->x*100,it->y*100);
	//}
	//glEnd(); 

	//glBegin(GL_POLYGON);
	//glColor3f(0,0,1);
	//for(vector<vector3>::iterator it=box2.vertices.begin();it!=box2.vertices.end();++it)
	//{
	//	glVertex2f(it->x*100,it->y*100);
	//}
	//glEnd(); 

	//glBegin(GL_LINES);
	//glColor3f(1,1,1);
	//glLineWidth(7.0);
	//glVertex2f(point1.x*100,point1.y*100);
	//glVertex2f(point2.x*100,point2.y*100);
	//glEnd();

	//glColor3f(0,1,0);
	//GLUquadricObj *objCylinder = gluNewQuadric();
	//gluCylinder(objCylinder, 200, 200, 700, 1000, 2000);

	//glBegin(GL_POLYGON);
	//glColor3f(0.8,0.8,0.8);
	//for(int i=0;i<1000;i++)
	//{
	//	glVertex2f(200*cos(i*CV_PI/500),200*sin(i*CV_PI/500));
	//}
	//glEnd(); 
   //glPointSize(5.0); 
   glBegin(GL_POINTS);
   glColor3f(0,0,1);
   for(vector<vector3>::iterator it=box1.vertices.begin();it!=box1.vertices.end();++it)
   {
	   glVertex3f(it->x*100,it->y*100,it->z*100);
   }
   glColor3f(0,1,0);
   for(vector<vector3>::iterator it=box2.vertices.begin();it!=box2.vertices.end();++it)
   {
	   glVertex3f(it->x*100,it->y*100,it->z*100);
   }
   //glPointSize(5.0);
   //glColor3f(1,1,1);
   //for(vector<vector3>::iterator it=mink.begin();it!=mink.end();++it)
   //{
	  // glVertex3f(it->x*100,it->y*100,it->z*100);
   //}
   //glPointSize(10.0);
   //glColor3f(1,0,0);
   //glVertex3f(point1.x*100,point1.y*100,point1.z*100);
   //glVertex3f(point2.x*100,point2.y*100,point2.z*100);
   //glVertex3f(point.x*100,point.y*100,point.z*100);

   glEnd();


   glBegin(GL_LINES);
   glColor3f(1,1,1);
   glVertex3f(gjk.point1.x*100,gjk.point1.y*100,gjk.point1.z*100);
   glVertex3f(gjk.point2.x*100,gjk.point2.y*100,gjk.point2.z*100);
   ////vector<vector3>::iterator it1=gjk.simplex.begin();
   ////cout<<gjk.simplex.size()<<endl;
   //for(vector<vector3>::iterator it1=gjk.simplex.begin();it1!=gjk.simplex.end();++it1)
   //{
	  // for(vector<vector3>::iterator it2=gjk.simplex.begin();it2!=gjk.simplex.end();++it2)
	  // {
		 //  glVertex3f(it1->x*100,it1->y*100,it1->z*100);
		 //  glVertex3f(it2->x*100,it2->y*100,it2->z*100);
	  // }
   //}
   //glVertex3f(gjk.a.x*100,gjk.a.y*100,gjk.a.z*100);
   //glVertex3f(gjk.b.x*100,gjk.b.y*100,gjk.b.z*100);
   //glVertex3f(gjk.b.x*100,gjk.b.y*100,gjk.b.z*100);
   //glVertex3f(gjk.c.x*100,gjk.c.y*100,gjk.c.z*100);
   //glVertex3f(gjk.c.x*100,gjk.c.y*100,gjk.c.z*100);
   //glVertex3f(gjk.a.x*100,gjk.a.y*100,gjk.a.z*100);
   //cout<<gjk.a.x<<","<<gjk.a.y<<","<<gjk.a.z<<endl;
   glEnd();

   glFlush();
   glutSwapBuffers();
}

void reshape (int w, int h) 
{
   glWinWidth = w;
   glWinHeight = h;
   glViewport (0, 0, (GLsizei)w, (GLsizei)h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective (45, (GLfloat)w / (GLfloat)h, 1.0, 15000.0);   
   glMatrixMode (GL_MODELVIEW);
}



int main(int argc, char **argv)
{
	clock_t start,end;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(10,200);
	glutInitWindowSize(640, 480);
	glutCreateWindow("3D image");

	//for(int i=0;i<3;i++)
	//{
	//	point.x=ver1[i][0];
	//	point.y=ver1[i][1];
	//	point.z=ver1[i][2];
	//	//cout<<point.x<<","<<point.y<<","<<point.z<<endl;
	//	box1.vertices.push_back(point);
	//}
	//for(vector<vector3>::iterator it=box1.vertices.begin();it!=box1.vertices.end();++it)
	//{
	//	cout<<it->x<<","<<it->y<<","<<it->z<<endl;
	//}
	//for(int i=0;i<4;i++)
	//{
	//	point.x=ver2[i][0];
	//	point.y=ver2[i][1];
	//	point.z=ver2[i][2];
	//	//cout<<point.x<<","<<point.y<<","<<point.z<<endl;
	//	box2.vertices.push_back(point);
	//}
	//for(vector<vector3>::iterator it=box2.vertices.begin();it!=box2.vertices.end();++it)
	//{
	//	cout<<it->x<<","<<it->y<<","<<it->z<<endl;
	//}

	//两个圆，等分10000份
	//for(int i=0;i<10000;i++)
	//{
	//	point.x=1+2*cos(i*CV_PI/5000);
	//	point.y=3+2*sin(i*CV_PI/5000);
	//	point.z=0;
	//	box1.vertices.push_back(point);
	//}
	//for(int i=0;i<10000;i++)
	//{
	//	point.x=9+3*cos(i*CV_PI/5000);
	//	point.y=1+3*sin(i*CV_PI/5000);
	//	point.z=0;
	//	box2.vertices.push_back(point);
	//}

	for(int i=0;i<N;i++)
	{
		point.x=2*cos(i*CV_PI*2/N);
		point.y=2*sin(i*CV_PI*2/N);
		for(int j=0;j<N*2;j++)
		{
			point.z=(double)j*7/(N*2);
			box1.vertices.push_back(point);
		}
	}
	cout<<"box1:"<<box1.vertices.size()<<endl;
	for(int i=0;i<N;i++)
	{
		point.x=(double)i*4/N;
		for(int j=0;j<N;j++)
		{
			point.y=5+(double)j*3/N;
			point.z=0;
			box2.vertices.push_back(point);
			point.z=4;
			box2.vertices.push_back(point);
		}
	}
	for(int i=0;i<N;i++)
	{
		point.x=(double)i*4/N;
		for(int j=0;j<N;j++)
		{
			point.z=(double)j*4/N;
			point.y=5;
			box2.vertices.push_back(point);
			point.y=8;
			box2.vertices.push_back(point);
		}
	}
	for(int i=0;i<N;i++)
	{
		point.y=5+(double)i*3/N;
		for(int j=0;j<N;j++)
		{
			point.z=(double)j*4/N;
			point.x=0;
			box2.vertices.push_back(point);
			point.x=4;
			box2.vertices.push_back(point);
		}
	}
	cout<<"box2:"<<box2.vertices.size()<<endl;


	//for(vector<vector3>::iterator it1=box1.vertices.begin();it1!=box1.vertices.end();++it1)
	//{
	//	for(vector<vector3>::iterator it2=box2.vertices.begin();it2!=box2.vertices.end();++it2)
	//	{
	//		point=*it1-*it2;
	//		mink.push_back(point);
	//	}
	//}

	//glutDisplayFunc(renderScene1);  


	start=clock();
	cout<<gjk.CollisionDetection(box1,box2)<<endl;
	end=clock();
	double distance=gjk.ClosestDistance(box1,box2);
	cout<<"distance using GJK:"<<distance<<endl;
	
	cout<<"time using GJK:"<<end-start<<"ms"<<endl;

	//vector3 a(1,-1,0);
	//vector3 b(1,1,0);
	//vector3 c(1,1,1);
	//vector3 p=gjk.ClosestPointToOrigin(a,b,c);
	//cout<<p.x<<","<<p.y<<","<<p.z<<endl;


	//vector3 dir(2,0,7);
	//vector3 p1=box1.getFarthestPointInDirection(dir);
	//vector3 p2=box2.getFarthestPointInDirection(dir);
	//cout<<"p1:"<<p1.x<<","<<p1.y<<","<<p1.z<<endl;
	//cout<<"p2:"<<p2.x<<","<<p2.y<<","<<p2.z<<endl;


	start=clock();
	double dis=1000000,dis_tmp;
	for(vector<vector3>::iterator it1=box1.vertices.begin();it1!=box1.vertices.end();++it1)
	{
		for(vector<vector3>::iterator it2=box2.vertices.begin();it2!=box2.vertices.end();++it2)
		{
			point=*it1-*it2;
			dis_tmp=point.length();
			if(dis_tmp<dis)
			{
				dis=dis_tmp;
				point1=*it1;
				point2=*it2;
			}
		}
	}
	end=clock();
	cout<<"distance:"<<dis<<endl;
	cout<<"time:"<<end-start<<"ms"<<endl;

	//dis=100000;
	//for(vector<vector3>::iterator it=mink.begin();it!=mink.end();++it)
	//{
	//	dis_tmp=it->length();
	//	if(dis_tmp<dis)
	//	{
	//		dis=dis_tmp;
	//	}
	//}
	//cout<<"distance using mink:"<<dis<<endl;

	//vector3 dir(1,1,1);
	//point1=gjk.support(box1,box2,dir);
	//cout<<"point1:"<<point1.x<<","<<point1.y<<","<<point1.z<<endl;
	//point2=gjk.support(box1,box2,-dir);
	//cout<<"point2:"<<point2.x<<","<<point2.y<<","<<point2.z<<endl;
	//dir=vector3::doubleCross(point1-point2,-point2);
	//point=gjk.support(box1,box2,dir);
	//cout<<"point:"<<point.x<<","<<point.y<<","<<point.z<<endl;
	
	while(1)
	{
		glutReshapeFunc (reshape); 
		glutDisplayFunc(renderScene1);
		glutMouseFunc(mouse);  
		glutSpecialFunc(key);
		glutMotionFunc(motion);
		glutPostRedisplay();    
		glutMainLoopEvent();
	}
	return 0;
}
