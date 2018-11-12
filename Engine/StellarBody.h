#pragma once

#include "BaseObject.h"

class StellarBody : public BaseObject
{
public:
	StellarBody(const char* Name, const char* ModelPath, const char* MaterialPath, const char* MaterialPath2);
	~StellarBody();

	virtual void OnRender(float DeltaTime) override;

	float OrbitDistance;
	float OrbitSpeed;
	float CurrentOrbigDegree;
};

