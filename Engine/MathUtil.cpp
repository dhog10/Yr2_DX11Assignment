#include "MathUtil.h"
#include <cstdlib>

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

XMFLOAT3 MathUtil::Cross(XMFLOAT3 a, XMFLOAT3 b)
{
	return XMFLOAT3(a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x);
}

XMFLOAT3 MathUtil::Normalize(XMFLOAT3 value)
{
	float magnitude = std::abs(value.x) + std::abs(value.y) + std::abs(value.z);

	return XMFLOAT3(value.x / magnitude, value.y / magnitude, value.z / magnitude);
}

XMMATRIX* MathUtil::DirectionToOrientation(XMFLOAT3 pos, XMFLOAT3 dir)
{
	XMVECTOR fwdVector = XMLoadFloat3(&dir);
	XMFLOAT3 up(0.0f, 1.0f, 0.0f);
	XMVECTOR upVector = XMLoadFloat3(&up);
	XMVECTOR sideVector = XMVector3Cross(upVector, fwdVector);
	upVector = XMVector3Cross(sideVector, fwdVector);

	upVector = XMVector3Normalize(upVector);
	sideVector = XMVector3Normalize(sideVector);

	XMFLOAT3 side;
	XMStoreFloat3(&side, sideVector);
	XMStoreFloat3(&up, upVector);
	XMFLOAT3 fwd;
	XMStoreFloat3(&fwd, fwdVector);

	XMMATRIX* pOrientation = new XMMATRIX(side.x, side.y, side.z, 0.0f,
		up.x, up.y, up.z, 0.0f,
		fwd.x, fwd.y, fwd.z, 0.0f,
		pos.x, pos.y, pos.z, 1.0f);

	return pOrientation;
}

float MathUtil::DotProduct(XMFLOAT3 a, XMFLOAT3 b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}
