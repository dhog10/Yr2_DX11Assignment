#include "StellarBody.h"
#include <math.h>


StellarBody::StellarBody(const char* Name, const char* ModelPath, const char* MaterialPath, const char* MaterialPath2)
	: BaseObject(Name, ModelPath, MaterialPath, MaterialPath2)
{
	SetModelPath(ModelPath);
	SetMaterialPath(MaterialPath);
	SetNormalPath(MaterialPath2);


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

	pPosition = new XMFLOAT3(cos(rad) * OrbitDistance, sin(rad) * OrbitDistance, 0);
}