/**
NIEE2211 - Computer Games Studio 2

Filename: StellarBody.cpp
Author: Daniel Lush
Date: 13/12/2018
*/

#include "StellarBody.h"
#include <math.h>


StellarBody::StellarBody(const char* Name, const char* ModelPath, WCHAR* MaterialPath, WCHAR* MaterialPath2)
	: BaseObject(Name, ModelPath, MaterialPath, MaterialPath2)
{
	SetModelPath(ModelPath);
	SetMaterialPath(MaterialPath);
	SetNormalPath(MaterialPath2);

	pOriginPosition = new XMFLOAT3(0.f, 0.f, 0.f);

	CurrentOrbigDegree = 0.f;
	OrbitSpeed = 0.f;
	OrbitDistance = 0.f;
}


StellarBody::~StellarBody()
{
}

void StellarBody::OnRender(float DeltaTime) {
	CurrentOrbigDegree += OrbitSpeed * DeltaTime;

	float rad = CurrentOrbigDegree * 0.0174533;

	pPosition = new XMFLOAT3((cos(rad) * OrbitDistance) + pOriginPosition->x, (sin(rad) * OrbitDistance) + pOriginPosition->y, pOriginPosition->z);
}