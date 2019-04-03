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

// The input frame struct is used to pass input into the object
struct InputFrame {
	float horizontal;
	float vertical;
};

struct VertexData {
	XMFLOAT3 vertices[8];
	int numIndices;
	XMFLOAT2 uv[8];
	int triangles[36];
	int numTriangles;
};

class BaseObject
{
private:
	const char* Name;

	D3DClass* pD3DClass;
	BaseObject* pParent;

	bool Initialized;

	// Collision
	bool mCollisionEnabled;
	bool mHoveringEnabled;
	bool mHovered;
	bool mDrawOBB;
	bool mDrawAABB;
	ObjectBoundingBox* pOBB = 0;
	ObjectBoundingBox* pAABB = 0;
	VertexData VerticesFromBoundingBox(ObjectBoundingBox* pBoundingBox);
protected:
	const char* pModelPath;
	WCHAR* pMaterialPath;
	WCHAR* pMaterialPath2;

	bool mDestroyed;
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
	XMMATRIX GetWorldMatrix(XMMATRIX origin, bool useRotation);

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

	virtual void OnInput(InputFrame inputFrame, float DeltaTime);
	virtual void OnRender(float DeltaTime);
	void OnCreate();
	void OnDestroy();
	void Destroy();
	bool IsDestroyed();

	bool bRotateFirst;
	bool bDontTransformParentRotation;

	BumpModelClass* pModelClass;
	class World* pWorld;

	bool operator==(BaseObject other);

	// Collision
	float mCollisionRadius;
	void EnableCollisions(bool enabled);
	void EnableHovering(bool enabled);
	bool GetCollisionsEnabled();
	bool GetHoveringEnabled();
	void ComputeOBB();
	void ComputeAABB();
	virtual void DoClick();
	virtual void DoHoverStart();
	virtual void DoHoverEnd();
	bool IsHovered();
	void SetHovered(bool);

	bool GetDrawOBB();
	bool GetDrawAABB();
	void SetDrawOBB(bool);
	void SetDrawAABB(bool);
	CollisionUtils* pCollisionUtil;

	bool mUseOrientationMatrix = false;
	XMMATRIX mOrientationMatrix;

	BumpModelClass* pOBBModel = 0;
	BumpModelClass* pAABBModel = 0;
};

