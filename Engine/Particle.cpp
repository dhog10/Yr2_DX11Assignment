#include "Particle.h"
#include "bumpmodelclass.h"
#include "ParticleSystem.h"

Particle::Particle()
{
	mPosition = XMFLOAT3(0, 0, 0);
	mVelocity = XMFLOAT3(0, 0, 0);
	mScale = 1.f;
	mLifetime = 1000.f;

	mCreated = timeGetTime();
}


Particle::~Particle()
{
}

void Particle::Initialize()
{
}

void Particle::OnRender(float deltaTime)
{
	float time = timeGetTime();
	float diff = time - mCreated;

	if (diff > mLifetime) {
		Destroy();
	}

	mPosition = XMFLOAT3(mPosition.x + (mVelocity.x * deltaTime), mPosition.y + (mVelocity.y * deltaTime), mPosition.z + (mVelocity.z * deltaTime));
}

void Particle::Destroy()
{
	mDestroyed = true;
}

XMMATRIX Particle::GetWorldMatrix(XMMATRIX worldMatrix, XMFLOAT3 rotation)
{
	worldMatrix = XMMatrixScaling(mScale, mScale, mScale);
	
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationX(rotation.x));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationX(rotation.y));
	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationX(rotation.z));

	XMMATRIX transformMatrix = XMMatrixTranslation(mPosition.x, mPosition.y, mPosition.z);
	worldMatrix = XMMatrixMultiply(worldMatrix, transformMatrix);

	return worldMatrix;
}
