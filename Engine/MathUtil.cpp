#include "MathUtil.h"


XMFLOAT3 MathUtil::AddFloat3(XMFLOAT3 a, XMFLOAT3 b)
{
	return XMFLOAT3(a.x + b.x, a.y + b.y, a.z + b.z);
}

XMFLOAT3 MathUtil::SubtractFloat3(XMFLOAT3 a, XMFLOAT3 b)
{
	return XMFLOAT3(a.x - b.x, a.y - b.y, a.z - b.z);
}

XMFLOAT3 MathUtil::MultiplyFloat3(XMFLOAT3 a, XMFLOAT3 b)
{
	return XMFLOAT3(a.x * b.x, a.y * b.y, a.z * b.z);
}

XMFLOAT3 MathUtil::MultiplyFloat3(XMFLOAT3 a, float n)
{
	return XMFLOAT3(a.x * n, a.y * n, a.z * n);
}

XMFLOAT3 MathUtil::DivideFloat3(XMFLOAT3 a, float n)
{
	return XMFLOAT3(a.x / n, a.y / n, a.z / n);
}

XMFLOAT3 MathUtil::AngleDirection(XMFLOAT3 angle)
{
	float degToRad = 0.0174533;
	angle = MultiplyFloat3(angle, degToRad);
	return XMFLOAT3(cos(angle.y) * cos(angle.x), sin(angle.y) * cos(angle.x), sin(angle.x));
}

XMFLOAT3 MathUtil::DirectionAngle(XMFLOAT3 dir)
{
	float radToDeg = 57.2958;

	float yaw = atan2(dir.x, dir.y) * radToDeg;
	float pitch = atan2(dir.z, sqrt((dir.x * dir.x) + (dir.y * dir.y))) * radToDeg;

	return XMFLOAT3(0.f, pitch, yaw);
}

XMFLOAT3 MathUtil::InvertFloat3(XMFLOAT3 value)
{
	return XMFLOAT3(-value.x, -value.y, -value.z);
}
