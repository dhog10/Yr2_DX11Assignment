#include "Parachuter.h"
#include "World.h"

Parachuter::Parachuter(const char* Name, const char* ModelPath, WCHAR* MaterialPath, WCHAR* MaterialPath2) : BaseObject::BaseObject(Name, ModelPath, MaterialPath, MaterialPath2)
{
	mCollisionRadius = 30;
}


Parachuter::~Parachuter()
{
}

void Parachuter::DoClick()
{
	pWorld->mScore++;
	Destroy();
}

void Parachuter::OnRender(float deltaTime)
{
	if (pPosition->y < 10) {
		Destroy();

		pWorld->mHealth--;

		if (pWorld->mHealth <= 0) {

		}
	}
}

