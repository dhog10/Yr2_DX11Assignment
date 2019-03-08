#pragma once

#include "d3dclass.h"

class BoundingBox
{
public:
	BoundingBox();
	BoundingBox(XMFLOAT3*, XMFLOAT3*);
	~BoundingBox();
	
	XMFLOAT3* pMins;
	XMFLOAT3* pMaxs;
};

