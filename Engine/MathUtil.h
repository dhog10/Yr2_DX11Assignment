#pragma once

#include "d3dclass.h"

class MathUtil
{
public:
	static XMFLOAT3 AddFloat3(XMFLOAT3, XMFLOAT3);
	static XMFLOAT3 SubtractFloat3(XMFLOAT3, XMFLOAT3);
	static XMFLOAT3 MultiplyFloat3(XMFLOAT3, XMFLOAT3);
	static XMFLOAT3 MultiplyFloat3(XMFLOAT3, float);
	static XMFLOAT3 DivideFloat3(XMFLOAT3, float);
	static XMFLOAT3 AngleDirection(XMFLOAT3);
	static XMFLOAT3 DirectionAngle(XMFLOAT3);
	static XMFLOAT3 InvertFloat3(XMFLOAT3);
	static XMFLOAT3 Cross(XMFLOAT3, XMFLOAT3);
};

