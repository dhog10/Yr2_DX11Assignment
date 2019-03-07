#include "BoundingBox.h"



BoundingBox::BoundingBox()
{
}

BoundingBox::BoundingBox(XMFLOAT3* pMins, XMFLOAT3* pMaxs) {
	this->pMins = pMins;
	this->pMaxs = pMaxs;
}


BoundingBox::~BoundingBox()
{
	delete pMins;
	delete pMaxs;
}
