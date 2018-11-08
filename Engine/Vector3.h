#pragma once
class Vector3
{
public:
	Vector3();
	Vector3(float, float, float);
	~Vector3();

	float x, y, z;

	Vector3& operator+ (Vector3 other);
};

