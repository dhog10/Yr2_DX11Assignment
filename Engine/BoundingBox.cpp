#include "BoundingBox.h"



ObjectBoundingBox::ObjectBoundingBox()
{
}

ObjectBoundingBox::ObjectBoundingBox(XMFLOAT3* pMins, XMFLOAT3* pMaxs) {
	this->pMins = pMins;
	this->pMaxs = pMaxs;
}


ObjectBoundingBox::~ObjectBoundingBox()
{
	delete pMins;
	delete pMaxs;
}
