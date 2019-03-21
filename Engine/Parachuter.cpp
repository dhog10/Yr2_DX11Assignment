#include "Parachuter.h"
#include "World.h"

Parachuter::Parachuter(const char* Name, const char* ModelPath, WCHAR* MaterialPath, WCHAR* MaterialPath2) : BaseObject::BaseObject(Name, ModelPath, MaterialPath, MaterialPath2)
{
	mCollisionRadius = 17;
}


Parachuter::~Parachuter()
{
}

void Parachuter::DoClick()
{
	Destroy();
}
