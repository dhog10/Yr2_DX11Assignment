#pragma once

#include "d3dclass.h"

class BaseObject;

class HitResult
{
public:
	HitResult();
	~HitResult();

	XMFLOAT3 mNormal;
	XMFLOAT3 mHitPos;
	float mHitDepth;

	static void ResolveCollision(HitResult*, BaseObject*, BaseObject*);
	static HitResult* AABB_AABB(BaseObject*, BaseObject*);
};

