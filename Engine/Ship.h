#pragma once

#include "BaseObject.h"

enum ShipType {
	DEFAULT,
	A,
	B,
	C,
	D,
	E,
};

class Ship : public BaseObject
{
public:
	Ship(const char* Name, const char* ModelPath, WCHAR* MaterialPath, WCHAR* MaterialPath2);
	~Ship();

	virtual void OnRender(float deltaTime);
	virtual void DoClick();

	void SetShipType(ShipType);
	void SetEnemy(bool);
	float mSpeed;
	bool mEnemy;

	XMFLOAT3 lastCameraPosition;
	XMFLOAT3 lastShipDirection;
};

