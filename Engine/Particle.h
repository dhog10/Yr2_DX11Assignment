#pragma once

#include "d3dclass.h"

class BumpModelClass;
class ParticleSystem;

class Particle
{
public:
	Particle();
	~Particle();

	ParticleSystem* pParticleSystem;
	WCHAR* pMaterial;

	void Initialize();
	void OnRender(float deltaTime);
	void Destroy();

	XMMATRIX GetWorldMatrix(XMMATRIX worldMatrix, XMFLOAT3 rotation);

	XMFLOAT3 mPosition;
	XMFLOAT3 mVelocity;

	bool mDestroyed = false;
	float mLifetime;
	float mScale;
private:
	float mCreated;
};

