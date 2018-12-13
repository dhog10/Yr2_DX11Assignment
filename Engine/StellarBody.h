/**
NIEE2211 - Computer Games Studio 2

Filename: StellarBody.h
Author: Daniel Lush
Date: 13/12/2018
*/

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

