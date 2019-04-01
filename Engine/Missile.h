#pragma once

#include "BaseObject.h"

class Missile : public BaseObject
{
public:
	Missile(const char* Name, const char* ModelPath, WCHAR* MaterialPath, WCHAR* MaterialPath2);
	~Missile();

	virtual void OnRender(float deltaTime);
	virtual void DoClick();

	float mMissileSpeed;
	BaseObject* pTarget;
};

