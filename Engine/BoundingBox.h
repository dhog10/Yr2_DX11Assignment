#pragma once

#include "d3dclass.h"

class ObjectBoundingBox
{
public:
	ObjectBoundingBox();
	ObjectBoundingBox(XMFLOAT3*, XMFLOAT3*);
	~ObjectBoundingBox();
	
	XMFLOAT3* pMins;
	XMFLOAT3* pMaxs;
};

