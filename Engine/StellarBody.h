#pragma once

#include "BaseObject.h"

class StellarBody : public BaseObject
{
public:
	StellarBody(const char* Name, const char* ModelPath, WCHAR* MaterialPath,WCHAR* MaterialPath2);
	~StellarBody();

	virtual void OnRender(float DeltaTime) override;

	XMFLOAT3* pOriginPosition;

	float OrbitDistance;
	float OrbitSpeed;
	float CurrentOrbigDegree;
};

