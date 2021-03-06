#pragma once

#include "BaseObject.h"

class Missile : public BaseObject
{
public:
	Missile(const char* Name, const char* ModelPath, WCHAR* MaterialPath, WCHAR* MaterialPath2);
	~Missile();

	virtual void DoClick();
	virtual void OnRender(float DeltaTime);
	virtual void OnCollide(BaseObject* pOther, HitResult* pHitResult);

	float mMissileSpeed;
	BaseObject* pTarget;

	float lastParticle = 0.f;
};

