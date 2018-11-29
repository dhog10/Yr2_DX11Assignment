#pragma once

#include "d3dclass.h"
#include "bumpmodelclass.h"

enum RenderShader { SHADED, UNLIT };

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
public:
	BaseObject(const char* Name, const char* ModelPath, WCHAR* MaterialPath, WCHAR* MaterialPath2);
	~BaseObject();

	int ID;

	void Initialize(D3DClass* pD3DClass);

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

	virtual void OnRender(float DeltaTime);
	void OnCreate();
	void OnDestroy();

	bool bRotateFirst;
	bool bDontTransformParentRotation;

	BumpModelClass* pModelClass;

	bool operator==(BaseObject other);
};

