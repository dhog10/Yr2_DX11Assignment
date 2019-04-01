#pragma once

#include "Ship.h"

class ShipSelect : public Ship
{
public:
	ShipSelect(const char* Name, const char* ModelPath, WCHAR* MaterialPath, WCHAR* MaterialPath2);
	~ShipSelect();

	float mHoverScale;

	virtual void DoClick();
	virtual void DoHoverStart();
	virtual void DoHoverEnd();
	virtual void OnRender(float deltaTime);
};

