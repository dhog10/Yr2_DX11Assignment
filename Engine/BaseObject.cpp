#include "BaseObject.h"
#include "World.h"

BaseObject::BaseObject(const char* Name, const char* ModelPath, WCHAR* MaterialPath, WCHAR* MaterialPath2)
{
	this->Name = Name;
	pScale = new XMFLOAT3(1.f, 1.f, 1.f);
	pPosition = new XMFLOAT3(0.f, 0.f, 0.f);
	pVelocity = new XMFLOAT3(0.f, 0.f, 0.f);
	pAngle = new XMFLOAT3(0.f, 0.f, 0.f);
	pAngularVelocity = new XMFLOAT3(0.f, 0.f, 0.f);

	pModelClass = new BumpModelClass;
	this->pModelPath = ModelPath;
	this->pMaterialPath = MaterialPath;
	this->pMaterialPath2 = MaterialPath2;

	renderShader = RenderShader::SHADED;

	pD3DClass = 0;
	pParent = 0;
	bRotateFirst = true;
	bDontTransformParentRotation = false;
	Initialized = false;
}

void BaseObject::Initialize(D3DClass* pD3DClass) {
	this->pD3DClass = pD3DClass;

	Initialized = true;

	if (pModelPath) {
		SetModelPath(pModelPath);
	}

	if (pMaterialPath) {
		SetMaterialPath(pMaterialPath);
	}

	if (pMaterialPath2) {
		SetNormalPath(pMaterialPath2);
	}
}

BaseObject::~BaseObject()
{
	if (pModelClass) {
		pModelClass->Shutdown();
		delete pModelClass;
		pModelClass = 0;
	}
	/*delete pScale;
	delete pPosition;
	delete pVelocity;
	delete pAngle;
	delete pAngularVelocity;
	delete pModelClass;*/
}

const char* BaseObject::GetName()
{
	return Name;
}

int BaseObject::GetID() {
	return ID;
}

void BaseObject::OnRender(float DeltaTime)
{
	// Moved position & angle manipulation to graphicsclass

	/*pPosition->x += pVelocity->x * DeltaTime;
	pPosition->y += pVelocity->y * DeltaTime;
	pPosition->z += pVelocity->z * DeltaTime;

	pAngle->x += pAngularVelocity->x * DeltaTime;
	pAngle->y += pAngularVelocity->y * DeltaTime;
	pAngle->z += pAngularVelocity->z * DeltaTime;*/
}

void BaseObject::OnCreate()
{

}

void BaseObject::OnDestroy()
{

}

bool BaseObject::operator==(BaseObject other)
{
	return ID == other.ID;
}

void BaseObject::SetModelPath(const char* ModelPath) {
	this->pModelPath = ModelPath;

	if (!Initialized) { return; }

	pModelClass = new BumpModelClass;

	HRESULT result = pModelClass->Initialize(pD3DClass->GetDevice(), (char*)ModelPath, GetMaterialPath(), GetNormalPath());

	// Args - D3D device, model path, texture path, texture path 2
}

const char* BaseObject::GetModelPath() {
	return pModelPath;
}

void BaseObject::SetMaterialPath(WCHAR* MaterialPath) {
	this->pMaterialPath = MaterialPath;
}

WCHAR* BaseObject::GetMaterialPath() {
	return pMaterialPath;
}

void BaseObject::SetNormalPath(WCHAR* NormalPath) {
	this->pMaterialPath2 = NormalPath;
}

WCHAR* BaseObject::GetNormalPath() {
	return pMaterialPath2;
}

void BaseObject::SetParent(BaseObject* pParent) {
	this->pParent = pParent;
}

BaseObject* BaseObject::GetParent() {
	return pParent;
}

XMMATRIX TransformRotation(XMMATRIX* pMatrix, XMFLOAT3* pAngle) {
	XMMATRIX Matrix = *pMatrix;

	if (pAngle->x != 0.f) {
		Matrix = XMMatrixMultiply(Matrix, XMMatrixRotationX(pAngle->x));
	}
	if (pAngle->y != 0.f) {
		Matrix = XMMatrixMultiply(Matrix, XMMatrixRotationY(pAngle->y));
	}
	if (pAngle->z != 0.f) {
		Matrix = XMMatrixMultiply(Matrix, XMMatrixRotationZ(pAngle->z));
	}

	return Matrix;
}

XMMATRIX TransformPosition(XMMATRIX* pMatrix, XMFLOAT3* pPosition) {
	XMMATRIX Matrix = *pMatrix;

	Matrix = XMMatrixMultiply(Matrix, XMMatrixTranslation(pPosition->x, pPosition->y, pPosition->z));

	return Matrix;
}

XMMATRIX CalculateWorldPosition(XMMATRIX* pOrigin, BaseObject* pObject, bool dontTransformRotation) {
	XMMATRIX origin = *pOrigin;
	XMFLOAT3* pAngle = pObject->pAngle;
	XMFLOAT3* pPosition = pObject->pPosition;

	if (pObject->bRotateFirst) {
		if (!dontTransformRotation) {
			origin = TransformRotation(&origin, pAngle);
		}
		origin = TransformPosition(&origin, pPosition);
	}
	else {
		if (!dontTransformRotation) {
			origin = TransformRotation(&origin, pAngle);
		}
		origin = TransformPosition(&origin, pPosition);
	}

	if (pObject->GetParent() != 0) {
		origin = CalculateWorldPosition(&origin, pObject->GetParent(), pObject->bDontTransformParentRotation);
	}

	return origin;
}

XMMATRIX BaseObject::GetWorldMatrix(XMMATRIX origin) {
	origin = XMMatrixScaling(pScale->x, pScale->y, pScale->z);

	return CalculateWorldPosition(&origin, this, false);
}

void BaseObject::SetScale(float scale) {
	pScale = new XMFLOAT3(scale, scale, scale);
}

void BaseObject::SetAngle(float p, float y, float r) {
	float DegToRad = 0.0174533f;

	pAngle = new XMFLOAT3(p * DegToRad, y * DegToRad, r * DegToRad);
}