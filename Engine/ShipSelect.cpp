#include "ShipSelect.h"
#include "World.h"


ShipSelect::ShipSelect(const char* Name, const char* ModelPath, WCHAR* MaterialPath, WCHAR* MaterialPath2) : Ship::Ship(Name, ModelPath, MaterialPath, MaterialPath2)
{
	mHoverScale = 0.15f;
	EnableCollisions(true);
	EnableHovering(true);
	mCollisionRadius = 80.f;
}


ShipSelect::~ShipSelect()
{
}

void ShipSelect::DoClick()
{
	pWorld->mPlayerShipType = GetShipType();
	pWorld->SetGameState(GameState::PLAY);
}

void ShipSelect::DoHoverStart()
{
}

void ShipSelect::DoHoverEnd()
{
}

void ShipSelect::OnRender(float DeltaTime)
{
	float currentScale = pScale->x;

	if (IsHovered()) {
		currentScale += (mHoverScale - currentScale) * DeltaTime * 6.f;
		SetScale(currentScale);
	}
	else {
		currentScale += (0.1f - currentScale) * DeltaTime * 6.f;
		SetScale(currentScale);
	}
}
