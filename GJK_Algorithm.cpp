#include "GJK_Algorithm.h"


GJK_Algorithm::GJK_Algorithm()
{
	a = b =c = d = vector3::zero();
	//nrPointsSimplex=0;
	//flag=false;
	simplex.clear();
}

GJK_Algorithm::~GJK_Algorithm()
{

}

 bool GJK_Algorithm::CollisionDetection(const Box& box1, const Box& box2)
{
	 simplex.clear();
	 vector3 dir = vector3(1, 1, 1);
		
	 simplex.push_back(support(box1, box2, dir));
	 dir.negate();
	 
		 	
	 //dir = -c;//negative direction

	 //b = support(box1, box2, dir);

	 //if (b.dot(dir) < 0)
	 //{
		// return false;
	 //}
	 //dir = vector3::doubleCross(c - b, -b);
	 //
	 //nrPointsSimplex = 3; //begin with 2 points in simplex
	
	 //int steps = 0;//avoid infinite loop
	 //while (steps<50)
	 while(true)
	 {
		 simplex.push_back(support(box1, box2, dir));


		 if ((*(simplex.end()-1)).dot(dir) <= 0)
		 {
			 return false;
		 }
		 else
		 {
			 
			 if (ContainsOrigin(dir))
			 {
				 //cout<<"a:"<<a.x<<","<<a.y<<","<<a.z<<endl;
				 //cout<<"b:"<<b.x<<","<<b.y<<","<<b.z<<endl;
				 //cout<<"c:"<<c.x<<","<<c.y<<","<<c.z<<endl;
				 //cout<<"d:"<<d.x<<","<<d.y<<","<<d.z<<endl;
				 return true;
			 }
		 }
		 //steps++;
		

	 }
	
	 //return false;
}

 double GJK_Algorithm::ClosestDistance(const Box& box1, const Box& box2)
 {
	 double tmp=0;
	 double dd;
	 double da,db,dc;

	 vector3 dir=vector3(1,1,1);
	 a=support(box1,box2,dir);
	 //dir=-a;
	 b=support(box1,box2,-dir);
	 dir = vector3::doubleCross(a - b, -b);//BA*BO*BA
	 c = support(box1, box2, dir);
	// int count=0;
	 while(true)
	 {

		// count++;
		 //cout<<"a:"<<a.x<<","<<a.y<<","<<a.z<<endl;
		 //cout<<"b:"<<b.x<<","<<b.y<<","<<b.z<<endl;
		 //cout<<"c:"<<c.x<<","<<c.y<<","<<c.z<<endl<<endl;
		 //dir=DirectionPointToOrigin(a,b,c);
		 dir=ClosestPointToOrigin(a,b,c);

		 //ClosestPoint=dir;
		 //cout<<"dir:"<<dir.x<<","<<dir.y<<","<<dir.z<<endl;
		 //if(dir.isZero())
		 //{
			// return -1;
		 //}
		 dir.negate();
		 dir.unit();
		 //cout<<dir.dot(a-b)<<endl;
		 //cout<<dir.dot(a-c)<<endl;
		 //cout<<dir.dot(b-c)<<endl;
		 //cout<<LineNormal(a,b,c).dot(c)<<endl;
		 //cout<<"d:"<<d.x<<","<<d.y<<","<<d.z<<endl;
		 d=support(box1,box2,dir);
		 point1=p1;
		 point2=p2;
		 //cout<<"dir.neg.unit:"<<dir.x<<","<<dir.y<<","<<dir.z<<endl;
		 //cout<<"d:"<<d.x<<","<<d.y<<","<<d.z<<endl;
		 //cout<<"tmp:"<<tmp.x<<","<<tmp.y<<","<<tmp.z<<endl;
		 //tmp=dd-da;
		 dd=d.dot(dir);
		 da=a.dot(dir);
		 db=b.dot(dir);
		 dc=c.dot(dir);
		 //cout<<"d:"<<d.x<<","<<d.y<<","<<d.z<<endl;
		 //cout<<"a:"<<a.x<<","<<a.y<<","<<a.z<<endl;
		 //cout<<"b:"<<b.x<<","<<b.y<<","<<b.z<<endl;
		 //cout<<"c:"<<c.x<<","<<c.y<<","<<c.z<<endl<<endl;
		 if(abs(da)<=abs(dc)&&abs(da)<=abs(db))
			 tmp=da;
		 else if(abs(db)<=abs(da)&&abs(db)<=abs(dc))
			 tmp=db;
		 else if(abs(dc)<=abs(da)&&abs(dc)<=abs(db))
			 tmp=dc;
		 //cout<<"dd:"<<dd<<",tmp:"<<tmp<<",dd-tmp:"<<dd-tmp<<endl<<endl;

		//glutDisplayFunc(renderScene1); 
		//while(true)
		//{
		//	glutReshapeFunc (reshape);         // 窗口变化时重绘图像
		//	glutMouseFunc(mouse);            // 鼠标按键响应
		//	glutSpecialFunc(key);
		//	glutMotionFunc(motion);            // 鼠标移动响应
		//	glutPostRedisplay();                  // 刷新画面
		//	glutMainLoopEvent();
		//	if(flag)
		//	{
		//		flag=false;
		//		break;
		//	}
		//}

		 if(dd-tmp<0.1)
		 {
			 //point1=p1;
			 //point2=p2;
			//cout<<"count:"<<count<<endl;
			if(dd>=0)
				return dd;
			else
				return -dd;
		 }

		 if(d==a||d==b||d==c)
		 {
			 continue;
		 }
		 else
		 {
			 if(a.length()>b.length()&&a.length()>c.length())
				 a=d;
			 else if(b.length()>a.length()&&b.length()>c.length())
				 b=d;
			 else if(c.length()>b.length()&&c.length()>a.length())
				 c=d;
		 }



	 }

 }

 bool GJK_Algorithm::ContainsOrigin(vector3& dir)
 {
	 a=*(simplex.end()-1);
	 vector3 ao= -a;
	 vector3 ab,ac,ad;
	 
	 if (simplex.size() == 2)
	 {
		 b=*(simplex.begin());
		 ab = b - a;
		 dir = vector3::doubleCross(ab, ao);
	 }
	 else if (simplex.size() == 3)
	 {
		 b=*(simplex.begin());
		 c=*(simplex.begin()+1);
		 ab = b - a;
		 ac = c - a;
		 vector3 abPerp=vector3::doubleCross2(ac,ab);
		 vector3 acPerp=vector3::doubleCross2(ab,ac);
		 if (abPerp.dot(ao) >= 0)
		 {
			simplex.erase(simplex.begin()+1);
			dir=abPerp;
		 }
		 else if(acPerp.dot(ao)>=0)
		 {
			simplex.erase(simplex.begin());
			dir=acPerp;
		 }
		 else
		 {
			 vector3 tmp=vector3::cross(ab,ac);
			 if(tmp.dot(ao)>0)
			 {
				 dir=tmp;
			 }
			 else
			 {
				 dir=-tmp;
			 }
		 }
	 }
	 else if(simplex.size()==4)
	 {
		 b=*(simplex.begin());
		 c=*(simplex.begin()+1);
		 d=*(simplex.begin()+2);
		 ab=b-a;
		 ac=c-a;
		 ad=d-a;
		 vector3 abcPerp=vector3::cross(ab,ac);
		 if(abcPerp.dot(ad)>0)
			 abcPerp.negate();
		 vector3 abdPerp=vector3::cross(ab,ad);
		 if(abdPerp.dot(ac)>0)
			 abdPerp.negate();
		 vector3 acdPerp=vector3::cross(ac,ad);
		 if(acdPerp.dot(ab)>0)
			 acdPerp.negate();
		 
		 if(abcPerp.dot(ao)>=0)
		 {
			 simplex.erase(simplex.begin()+2);
			 dir=abcPerp;
		 }
		 else if(abdPerp.dot(ao)>=0)
		 {
			 simplex.erase(simplex.begin()+1);
			 dir=abdPerp;
		 }
		 else if(acdPerp.dot(ao)>=0)
		 {
			 simplex.erase(simplex.begin());
			 dir=acdPerp;
		 }
		 else
			 return true;
	 }
				 //cout<<"a:"<<a.x<<","<<a.y<<","<<a.z<<endl;
				 //cout<<"b:"<<b.x<<","<<b.y<<","<<b.z<<endl;
				 //cout<<"c:"<<c.x<<","<<c.y<<","<<c.z<<endl;
				 //cout<<"d:"<<d.x<<","<<d.y<<","<<d.z<<endl<<endl;
	 return false;
 }

 vector3 GJK_Algorithm::support(Box a,Box b, const vector3& dir)
 {
	 p1 = a.getFarthestPointInDirection(dir);
	 p2 = b.getFarthestPointInDirection(vector3(-dir.x, -dir.y, -dir.z));

	 //p2 -p1
	 vector3 p3 = p1 - p2;

	return  p3;
 }

vector3 GJK_Algorithm::ClosestPointToOrigin(vector3& a, vector3& b, vector3& c)
{
	vector3 pab=ClosestPointToOriginFromLine(a,b);
	vector3 pac=ClosestPointToOriginFromLine(a,c);
	vector3 pbc=ClosestPointToOriginFromLine(b,c);
	//cout<<pab.dot(a-b)<<endl;
	//cout<<pac.dot(a-c)<<endl;
	//cout<<pbc.dot(b-c)<<endl;
	//cout<<"pab:"<<pab.x<<","<<pab.y<<","<<pab.z<<endl;
	//cout<<"pac:"<<pac.x<<","<<pac.y<<","<<pac.z<<endl;
	//cout<<"pbc:"<<pbc.x<<","<<pbc.y<<","<<pbc.z<<endl<<endl;
	vector3 o(0,0,0);
	if(pab==a&&pac==a)
	{
		return a;
	}
	else if(pbc==b&&pab==b)
	{
		return b;
	}
	else if(pac==c&&pbc==c)
	{
		return c;
	}
	else if(LineNormal(a,b,c).dot(LineNormal(a,b,o))<=0)
	{
		cout<<LineNormal(a,b,c).dot(a-b)<<endl;
		cout<<LineNormal(a,b,o).dot(a-b)<<endl;
		return pab;
	}
	else if(LineNormal(a,c,b).dot(LineNormal(a,c,o))<=0)
	{
		cout<<LineNormal(a,c,b).dot(a-c)<<endl;
		cout<<LineNormal(a,c,o).dot(a-c)<<endl;
		return pac;
	}
	else if(LineNormal(b,c,a).dot(LineNormal(b,c,o))<=0)
	{
		cout<<LineNormal(b,c,a).dot(b-c)<<endl;
		cout<<LineNormal(b,c,o).dot(b-c)<<endl;
		return pbc;
	}
	else
	{
		vector3 ab(b-a);
		vector3 ac(c-a);
		//vector3 ao(-a);
		vector3 n=ab.cross(ac);
		double t=(n.x*a.x+n.y*a.y+n.z+a.z)/(n.x*n.x+n.y*n.y+n.z*n.z);
		vector3 p(t*n.x,t*n.y,t*n.z);

		//double t1 = ao.dot(ab);
		//double t2 = ab.dot(ab);
		//double t = t1/t2;
		//vector3 tmp(ab.x*t, ab.y*t, ab.z*t);
		//vector3 p(tmp+a);

		//vector3 cp(p-c);
		//vector3 co(-c);
		//t1=co.dot(cp);
		//t2=cp.dot(cp);
		//t=t1/t2;
		//tmp=vector3(cp.x*t,cp.y*t,cp.z*t);
		//vector3 pp(tmp+c);
		return p;
	}
}

vector3 GJK_Algorithm::ClosestPointToOriginFromLine(vector3& a, vector3& b)
{
	vector3 ab(b-a);
	vector3 ao(-a);
	vector3 ba(a-b);
	vector3 bo(-b);
	if(ab.dot(ao)<=0)
		return a;
	else if(ba.dot(bo)<=0)
		return b;
	else
	{
		double t1 = ao.dot(ab);
		double t2 = ab.dot(ab);
		double t = t1/t2;
		vector3 tmp(ab.x*t, ab.y*t, ab.z*t);
		vector3 p(tmp+a);
		return p;
	}
}

// line ab, point c
vector3 GJK_Algorithm::LineNormal(vector3& a, vector3& b, vector3& c)
{
	vector3 ab(b-a);
	vector3 ac(c-a);
	double t1 = ac.dot(ab);
	double t2 = ab.dot(ab);
	double t = t1/t2;
	vector3 tmp(ab.x*t, ab.y*t, ab.z*t);
	vector3 p(tmp+a);
	return c-p;
}

vector3 GJK_Algorithm::DirectionPointToOrigin(vector3& a, vector3& b, vector3& c)
{
	vector3 ab(b-a);
	vector3 ac(c-a);
	vector3 ao(-a);
	vector3 dir=vector3::cross(ab,ac);
	dir.unit();
	if(dir.dot(ao)>0)
		return dir;
	else
		return -dir;
}

