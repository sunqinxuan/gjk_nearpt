#include "vector.h"

vector3::vector3() : x(0.0), y(0.0), z(0.0) { }
vector3::vector3(double x, double y, double z) : x(x), y(y), z(z) { }

double vector3::operator*(const vector3& v) {
	return this->x*v.x + this->y*v.y + this->z*v.z;
}

vector3 vector3::cross(const vector3& v) {
	return vector3(this->y*v.z - this->z*v.y, this->z*v.x - this->x*v.z, this->x*v.y - this->y*v.x);
}

double vector3::dot(const vector3& v) {
	return this->x*v.x + this->y*v.y + this->z*v.z;
}

vector3 vector3::operator+(const vector3& v) {
	return vector3(this->x + v.x, this->y + v.y, this->z + v.z);
}

vector3 vector3::operator-(const vector3& v) {
	return vector3(this->x - v.x, this->y - v.y, this->z - v.z);
}
vector3 vector3::operator-() const {
	return vector3( -this->x, -this->y, - this->z);
}

vector3 vector3::operator*(const float s) {
	return vector3(this->x*s, this->y*s, this->z*s);
}

vector3& vector3::operator=(const vector3& v) {
	this->x = v.x; this->y = v.y; this->z = v.z;
	return *this;
}

bool vector3::operator==(const vector3& v) {
	if( this->x == v.x&& this->y == v.y&& this->z == v.z)
		return true;
	else
		return false;
}


double vector3::length() {
	return sqrt(this->x*this->x + this->y*this->y + this->z*this->z);
}

void vector3::unit() {
	float l = this->length();
	this->x = this->x/l;
	this->y = this->y/l;
	this->z = this->z/l;
}

void vector3::negate() {
	this->x = -this->x;
	this->y = -this->y;
	this->z = -this->z;
}

//STATIC METHODS
vector3 vector3::zero()
{
	return vector3(0, 0, 0);
}

vector3 vector3::cross(const vector3& v1, const vector3& v2)
{
	return vector3(v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x);
}
vector3 vector3::doubleCross(const vector3& v1, const vector3& v2)
{
	return cross(cross(v1, v2), v1);
}

vector3 vector3::doubleCross2(const vector3& v1, const vector3& v2)
{
	return cross(cross(v1, v2), v2);
}

bool vector3::isZero()
{
	if(this->x==0&&this->y==0&&this->z==0)
		return true;
	else
		return false;
}


