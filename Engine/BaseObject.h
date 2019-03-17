/**
NIEE2211 - Computer Games Studio 2

Filename: BaseObject.h
Author: Daniel Lush
Date: 13/12/2018
*/

#pragma once

#ifndef BOBJECT
#define BOBJECT

#include "CollisionUtils.h"
#include "d3dclass.h"
#include "bumpmodelclass.h"
#include "BoundingBox.h"
#include <map>

#endif

enum RenderShader { SHADED, UNLIT, SHADED_NO_BUMP, SHADED_FOG };

class BaseObject
{
private:
	const char* Name;

	const char* pModelPath;
	WCHAR* pMaterialPath;
	WCHAR* pMaterialPath2;

	D3DClass* pD3DClass;
	BaseObject* pParent;

	bool Initialized;

	// Collision
	bool CollisionEnabled;
	BoundingBox* pBoundingBox = 0;
public:
	BaseObject(const char* Name, const char* ModelPath, WCHAR* MaterialPath, WCHAR* MaterialPath2);
	~BaseObject();

	int ID;

	void Initialize(D3DClass* pD3DClass);
	bool IsInitialized();

	void SetModelPath(const char*);
	const char* GetModelPath();
	void SetMaterialPath(WCHAR*);
	WCHAR* GetMaterialPath();
	void SetNormalPath(WCHAR*);
	WCHAR* GetNormalPath();
	void SetParent(BaseObject* pParent);
	BaseObject* GetParent();
	XMMATRIX GetWorldMatrix(XMMATRIX origin);

	RenderShader renderShader;

	const char* GetName();
	int GetID();

	XMFLOAT3 * pScale;
	XMFLOAT3 * pPosition;
	XMFLOAT3 * pVelocity;
	XMFLOAT3 * pAngle;
	XMFLOAT3 * pAngularVelocity;

	void SetScale(float scale);
	void SetAngle(float, float, float);
	XMFLOAT3 GetAngle();

	virtual void OnRender(float DeltaTime);
	void OnCreate();
	void OnDestroy();

	bool bRotateFirst;
	bool bDontTransformParentRotation;

	BumpModelClass* pModelClass;

	class World* pWorld;

	bool operator==(BaseObject other);

	// Collision
	void EnableCollisions(bool enabled);
	bool GetCollisionsEnabled();
	void ComputeBoundingBox();
	CollisionUtils* pCollisionUtil;
};

