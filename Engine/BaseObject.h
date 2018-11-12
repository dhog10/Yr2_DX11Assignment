#pragma once

#include "d3dclass.h"
#include "bumpmodelclass.h"

class BaseObject
{
private:
	const char* Name;

	const char* pModelPath;
	const char* pMaterialPath;
	const char* pMaterialPath2;

	D3DClass* pD3DClass;
	BaseObject* pParent;

	bool Initialized;
public:
	BaseObject(const char* Name, const char* ModelPath, const char* MaterialPath, const char* MaterialPath2);
	~BaseObject();

	int ID;

	void Initialize(D3DClass* pD3DClass);

	void SetModelPath(const char*);
	const char* GetModelPath();
	void SetMaterialPath(const char*);
	const char* GetMaterialPath();
	void SetNormalPath(const char*);
	const char* GetNormalPath();
	void SetParent(BaseObject* pParent);
	BaseObject* GetParent();
	XMMATRIX GetWorldPosition(XMMATRIX origin);

	const char* GetName();
	int GetID();

	XMFLOAT3 * pScale;
	XMFLOAT3 * pPosition;
	XMFLOAT3 * pVelocity;
	XMFLOAT3 * pAngle;
	XMFLOAT3 * pAngularVelocity;

	virtual void OnRender(float DeltaTime);
	void OnCreate();
	void OnDestroy();

	bool bRotateFirst;

	BumpModelClass* pModelClass;

	bool operator==(BaseObject other);
};

