#pragma once

#include "d3dclass.h"
#include "bumpmodelclass.h"

class BaseObject
{
private:
	const char* Name;
	int ID;

	const char* pModelPath;
	const char* pMaterialPath;
	const char* pMaterialPath2;

	D3DClass* pD3DClass;
public:
	BaseObject(const char* Name, int ID, const char* ModelPath, const char* MaterialPath, const char* MaterialPath2);
	~BaseObject();

	void Initialize(D3DClass* pD3DClass);

	void SetModelPath(const char*);
	const char* GetModelPath();
	void SetMaterialPath(const char*);
	const char* GetMaterialPath();
	void SetNormalPath(const char*);
	const char* GetNormalPath();

	const char* GetName();
	int GetID();

	XMFLOAT3 * pScale;
	XMFLOAT3 * pPosition;
	XMFLOAT3 * pVelocity;
	XMFLOAT3 * pAngle;
	XMFLOAT3 * pAngularVelocity;

	void OnRender(float);
	void OnCreate();
	void OnDestroy();

	BumpModelClass* pModelClass;

	bool operator==(BaseObject other);
};

