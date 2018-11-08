#include "BaseObject.h"



BaseObject::BaseObject(const char* Name, int ID, const char* ModelPath, const char* MaterialPath, const char* MaterialPath2)
{
	this->Name = Name;
	this->ID = ID;
	pScale = new XMFLOAT3(0.f, 0.f, 0.f);
	pPosition = new XMFLOAT3(0.f, 0.f, 0.f);
	pVelocity = new XMFLOAT3(0.f, 0.f, 0.f);
	pAngle = new XMFLOAT3(0.f, 0.f, 0.f);
	pAngularVelocity = new XMFLOAT3(0.f, 0.f, 0.f);

	pModelClass = new BumpModelClass;
	this->pModelPath = ModelPath;
	this->pMaterialPath = MaterialPath;
	this->pMaterialPath2 = MaterialPath2;

	pParent = 0;
	bRotateFirst = true;
}

void BaseObject::Initialize(D3DClass* pD3DClass) {
	this->pD3DClass = pD3DClass;

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
	pPosition->x += pVelocity->x * DeltaTime;
	pPosition->y += pVelocity->y * DeltaTime;
	pPosition->z += pVelocity->z * DeltaTime;

	pAngle->x += pAngularVelocity->x * DeltaTime;
	pAngle->y += pAngularVelocity->y * DeltaTime;
	pAngle->z += pAngularVelocity->z * DeltaTime;
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

	if (!pD3DClass) { return; }

	pModelClass = new BumpModelClass;

	HRESULT result = pModelClass->Initialize(pD3DClass->GetDevice(), (char*)ModelPath, L"../Engine/data/stone.dds", L"../Engine/data/normal.dds");

	// Args - D3D device, model path, texture path, texture path 2
}

const char* BaseObject::GetModelPath() {
	return pModelPath;
}

void BaseObject::SetMaterialPath(const char* MaterialPath) {
	this->pMaterialPath = MaterialPath;
}

const char* BaseObject::GetMaterialPath() {
	return pMaterialPath;
}

void BaseObject::SetNormalPath(const char* NormalPath) {
	this->pMaterialPath2 = NormalPath;
}

const char* BaseObject::GetNormalPath() {
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

XMMATRIX BaseObject::GetWorldPosition(XMMATRIX origin) {
	//if (true) { return origin; }

	if (bRotateFirst) {
		origin = TransformRotation(&origin, pAngle);

		if (pParent) {
			origin = pParent->GetWorldPosition(origin);
		}

		origin = TransformPosition(&origin, pPosition);
	}
	else {
		XMMATRIX LocalOriginMatrix = TransformPosition(&origin, pPosition);

		origin = TransformRotation(&LocalOriginMatrix, pAngle);

		if (pParent) {
			origin = pParent->GetWorldPosition(origin);
		}

		origin = TransformPosition(&origin, pPosition);
		
	}

	return origin;
}