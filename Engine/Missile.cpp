#include "Missile.h"
#include "MathUtil.h"
#include "World.h"
#include "ParticleSystem.h"
#include "Particle.h"

Missile::Missile(const char * Name, const char * ModelPath, WCHAR * MaterialPath, WCHAR * MaterialPath2) : BaseObject::BaseObject(Name, ModelPath, MaterialPath, MaterialPath2)
{
	pModelPath = "../Engine/data/missile/missile.obj";
	pMaterialPath = L"../Engine/data/missile/missile.dds";
	pMaterialPath2 = L"../Engine/data/missile/missile.dds";

	mMissileSpeed = 120.f;
	SetScale(0.2f);
}

Missile::~Missile()
{
}

void Missile::DoClick()
{
}

void Missile::OnRender(float DeltaTime)
{
	if (pTarget) {
		XMFLOAT3 direction = MathUtil::Normalize(MathUtil::SubtractFloat3(*pTarget->pPosition, *pPosition));
		XMFLOAT3 vel = MathUtil::MultiplyFloat3(direction, mMissileSpeed);
		pVelocity = new XMFLOAT3(vel.x, vel.y, vel.z);

		XMFLOAT3 pos = *pPosition;

		XMVECTOR posVector = XMLoadFloat3(pPosition);
		XMVECTOR dirVector = XMLoadFloat3(&direction);
		XMFLOAT3 up = XMFLOAT3(0, 1, 0);
		XMVECTOR upVector = XMLoadFloat3(&up);

		//mUseOrientationMatrix = true;
		//XMMATRIX lookAtMatrix = XMMatrixLookAtLH(posVector, posVector + dirVector, upVector);
		//mOrientationMatrix = lookAtMatrix;
		// mOrientationMatrix = MathUtil::DirectionToOrientation(*pPosition, direction);

		float radToDeg = 57.2958f;

		//XMFLOAT3 directionAngle = MathUtil::MultiplyFloat3(direction, 360.f);
		XMFLOAT3 directionAngle = MathUtil::DirectionAngle(direction);
		SetAngle(0.f, -directionAngle.z, -directionAngle.y);

		float time = timeGetTime();
		if (time - lastParticle > 100.f) {
			lastParticle = time;
			
			Particle* pParticle = pWorld->pParticleSystem->CreateParticle(L"../Engine/data/missile/missile.dds");
			pParticle->mPosition = XMFLOAT3(pPosition->x, pPosition->y, pPosition->z);
			pParticle->mLifetime = 1000.f;
			pParticle->mScale = 1.f;

		}
	}
}
