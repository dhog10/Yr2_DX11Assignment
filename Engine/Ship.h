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
private:
	ShipType mShipType;
public:
	Ship(const char* Name, const char* ModelPath, WCHAR* MaterialPath, WCHAR* MaterialPath2);
	~Ship();

	void FireMissile(BaseObject* pTarget);
	virtual void OnRender(float deltaTime);
	virtual void DoClick();
	virtual void OnInput(InputFrame, float);
	void SetShipType(ShipType);
	ShipType GetShipType();
	void SetEnemy(bool);
	void SetShipSpeed(float);
	float mSpeed;
	float mMaxSpeed;
	float mMinSpeed;
	float mAcceleration;

	bool mEnemy;
	bool mPlayerShip;

	XMFLOAT3 lastCameraPosition;
	XMFLOAT3 lastShipDirection;
};

