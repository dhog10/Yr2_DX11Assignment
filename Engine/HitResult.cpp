#include "HitResult.h"
#include "BaseObject.h"
#include "MathUtil.h"

HitResult::HitResult()
{
}


HitResult::~HitResult()
{
}

void HitResult::ResolveCollision(HitResult * pHitResult, BaseObject * a, BaseObject * b)
{
	if (a->mStatic && b->mStatic) { return; }

	// Resolve impulses between the two objects
	XMFLOAT3 relativeVelocity = MathUtil::SubtractFloat3(*b->pVelocity, *a->pVelocity);
	float contactVelocity = MathUtil::DotProduct(relativeVelocity, pHitResult->mNormal);

	//if (contactVelocity < 0) {
		// Only resolve impulses if the objects are moving towards each other

		float restitution = 0.1f;
		float impulseScalar = (-1.0f + restitution) * contactVelocity;

		float massA = 1.f; //A->mMass;
		float massB = 1.f; //B->mMass;

		impulseScalar /= massA + massB;

		XMFLOAT3 impulse = MathUtil::MultiplyFloat3(pHitResult->mNormal, impulseScalar);

		float impulseMultiplier = 10.f;

		XMFLOAT3 impulseA = XMFLOAT3(-impulse.x * massA * impulseMultiplier, -impulse.y * massA * impulseMultiplier, -impulse.y * massA * impulseMultiplier);
		XMFLOAT3 impulseB = XMFLOAT3(impulse.x * massB * impulseMultiplier, impulse.y * massB * impulseMultiplier, impulse.y * massB * impulseMultiplier);

		// Apply impulses
		if (!a->mStatic) {
			a->pVelocity = new XMFLOAT3(a->pVelocity->x + impulseA.x, a->pVelocity->y + impulseA.y, a->pVelocity->z + impulseA.z);
		}
		if (!b->mStatic) {
			b->pVelocity = new XMFLOAT3(b->pVelocity->x + impulseB.x, b->pVelocity->y + impulseB.y, b->pVelocity->z + impulseB.z);
		}
	//}
}

HitResult * HitResult::AABB_AABB(BaseObject * a, BaseObject * b)
{
	ObjectBoundingBox* pAABB1 = a->pAABB;
	ObjectBoundingBox* pAABB2 = b->pAABB;

	if (pAABB1 == NULL || pAABB2 == NULL) { return NULL; }

	XMFLOAT3* pPosA = a->pPosition;
	XMFLOAT3* pPosB = b->pPosition;

	XMFLOAT3 maxA = XMFLOAT3(pAABB1->pMaxs->x, pAABB1->pMaxs->y, pAABB1->pMaxs->z);
	XMFLOAT3 minA = XMFLOAT3(pAABB1->pMins->x, pAABB1->pMins->y, pAABB1->pMins->z);
	maxA = MathUtil::MultiplyFloat3(maxA, *a->pScale);
	minA = MathUtil::MultiplyFloat3(minA, *a->pScale);

	XMFLOAT3 maxB = XMFLOAT3(pAABB2->pMaxs->x, pAABB2->pMaxs->y, pAABB2->pMaxs->z);
	XMFLOAT3 minB = XMFLOAT3(pAABB2->pMins->x, pAABB2->pMins->y, pAABB2->pMins->z);
	maxB = MathUtil::MultiplyFloat3(maxB, *b->pScale);
	minB = MathUtil::MultiplyFloat3(minB, *b->pScale);

	XMFLOAT3 extA = MathUtil::MultiplyFloat3(MathUtil::SubtractFloat3(maxA, minA), 0.5f);
	XMFLOAT3 extB = MathUtil::MultiplyFloat3(MathUtil::SubtractFloat3(maxB, minB), 0.5f);

	if (pPosA->x + extA.x < pPosB->x - extB.x) { return NULL; }
	if (pPosA->y + extA.y < pPosB->y - extB.y) { return NULL; }
	if (pPosA->z + extA.z < pPosB->z - extB.z) { return NULL; }
	if (pPosA->x - extA.x > pPosB->x + extB.x) { return NULL; }
	if (pPosA->y - extA.y > pPosB->y + extB.y) { return NULL; }
	if (pPosA->z - extA.x > pPosB->z + extB.z) { return NULL; }

	HitResult* pHitResult = new HitResult();
	pHitResult->mHitDepth = 0.f;
	pHitResult->mHitPos = MathUtil::AddFloat3(*pPosA, extA);
	pHitResult->mNormal = MathUtil::Normalize(MathUtil::SubtractFloat3(*pPosB, *pPosA));

	return pHitResult;
}
