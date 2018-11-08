#include "Vector3.h"


Vector3::Vector3()
{
	x = 0.f;
	y = 0.f;
	z = 0.f;
}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}


Vector3::~Vector3()
{
}

Vector3& Vector3::operator+(Vector3 other)
{
	return new Vector3(this->x + other.x, this->y + other.y, this->z + other.z);
}