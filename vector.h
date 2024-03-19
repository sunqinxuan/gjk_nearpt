#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

class vector3 {
  private:
  protected:
  public:
    double x, y, z;


    vector3();
	vector3(double x, double y, double z);

	
    vector3 cross(const vector3& v);
	double dot(const vector3& v);

	double operator*(const vector3& v);
    vector3 operator+(const vector3& v);

    vector3 operator-(const vector3& v);
	vector3 operator-() const;

    vector3 operator*(const float s);
    vector3& operator=(const vector3& v);
	bool operator==(const vector3& v);
	

	double length();
    void unit();
	void negate();

	static vector3 zero();
	static vector3 cross(const vector3& v1, const vector3& v2);
	static vector3 doubleCross(const vector3& v1, const vector3& v2);
	static vector3 doubleCross2(const vector3& v1, const vector3& v2);

	bool isZero();
};


#endif