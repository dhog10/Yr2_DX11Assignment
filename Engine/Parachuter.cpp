#include "Parachuter.h"
#include "World.h"
#include "Ship.h"

Parachuter::Parachuter(const char* Name, const char* ModelPath, WCHAR* MaterialPath, WCHAR* MaterialPath2) : BaseObject::BaseObject(Name, ModelPath, MaterialPath, MaterialPath2)
{
	mCollisionRadius = 30;

	SetDrawAABB(true);
	EnableCollisions(true);

	mStatic = true;
}


Parachuter::~Parachuter()
{
}

void Parachuter::DoClick()
{
	// pWorld->mScore++;
	// Destroy();

	Ship* pPlayerShip = pWorld->GetPlayerShip();
	if (pPlayerShip != NULL) {
		pPlayerShip->FireMissile(this);
	}
}

void Parachuter::OnRender(float deltaTime)
{
	if (pPosition->y < 10) {
		Destroy();

		if (pWorld->mHealth > 0) {
			pWorld->mHealth--;
		}
	}
}

