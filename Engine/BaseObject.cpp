/**
NIEE2211 - Computer Games Studio 2

Filename: BaseObject.cpp
Author: Daniel Lush
Date: 13/12/2018
*/

#include "BaseObject.h"
#include "World.h"
#include "graphicsclass.h"

// The base object class is a generic class which contains information which all objects can use for common purposes
// This reduces the amount of repeated code and allows for faster addition of many objects

VertexData BaseObject::VerticesFromBoundingBox(BoundingBox * pBoundingBox)
{

	XMFLOAT3 min = *pBoundingBox->pMins;
	XMFLOAT3 max = *pBoundingBox->pMaxs;
	XMFLOAT3 diff = XMFLOAT3(max.x - min.x, max.y - min.y, max.z - min.z);

	VertexData data = VertexData();
	data.numIndices = 24;
	data.numTriangles = 36;

	data.vertices[0] = XMFLOAT3(0, 0, 0);//side1
	data.uv[0] = XMFLOAT2(1 / 6.f, 0);
	data.vertices[1] = XMFLOAT3(diff.x, 0, 0);//side1
	data.uv[1] = XMFLOAT2(0 / 6.f, 0);
	data.vertices[2] = XMFLOAT3(0, diff.y, 0);//side1
	data.uv[2] = XMFLOAT2(1 / 6.f, 1);
	data.vertices[4] = XMFLOAT3(diff.x, diff.y, 0);//side1
	data.uv[4] = XMFLOAT2(0 / 6.f, 1);
	data.vertices[3] = XMFLOAT3(0, 0, diff.z); //side2
	data.uv[3] = XMFLOAT2(1 / 6.f, 0);
	data.vertices[8] = XMFLOAT3(0, diff.y, 0); //side2
	data.uv[8] = XMFLOAT2(2 / 6.f, 1);
	data.vertices[5] = XMFLOAT3(0, diff.y, diff.z);//side2
	data.uv[5] = XMFLOAT2(1 / 6.f, 1);
	data.vertices[9] = XMFLOAT3(0, 0, 0);//side2
	data.uv[9] = XMFLOAT2(2 / 6.f, 0);
	data.vertices[10] = XMFLOAT3(0, diff.y, diff.z);//side3
	data.uv[10] = XMFLOAT2(3 / 6.f, 1);
	data.vertices[6] = XMFLOAT3(diff.x, 0, diff.z);//side3
	data.uv[6] = XMFLOAT2(2 / 6.f, 0);
	data.vertices[7] = XMFLOAT3(diff.x, diff.y, diff.z);//side3
	data.uv[7] = XMFLOAT2(2 / 6.f, 1);
	data.vertices[11] = XMFLOAT3(0, 0, diff.z);//side3
	data.uv[11] = XMFLOAT2(3 / 6.f, 0);
	data.vertices[12] = XMFLOAT3(diff.x, diff.y, diff.z);//side4
	data.uv[12] = XMFLOAT2(4 / 6.f, 1);
	data.vertices[13] = XMFLOAT3(diff.x, 0, diff.z);//side4
	data.uv[13] = XMFLOAT2(4 / 6.f, 0);
	data.vertices[14] = XMFLOAT3(diff.x, diff.y, 0);//side4
	data.uv[14] = XMFLOAT2(3 / 6.f, 1);
	data.vertices[15] = XMFLOAT3(diff.x, 0, 0);//side4
	data.uv[15] = XMFLOAT2(3 / 6.f, 0);
	data.vertices[16] = XMFLOAT3(0, 0, 0);//bottom
	data.uv[16] = XMFLOAT2(5 / 6.f, 0);
	data.vertices[17] = XMFLOAT3(diff.x, 0, diff.z);//bottom
	data.uv[17] = XMFLOAT2(4 / 6.f, 1);
	data.vertices[18] = XMFLOAT3(0, 0, diff.z);//bottom
	data.uv[18] = XMFLOAT2(5 / 6.f, 1);
	data.vertices[19] = XMFLOAT3(diff.x, 0, 0);//bottom
	data.uv[19] = XMFLOAT2(4 / 6.f, 0);
	data.vertices[20] = XMFLOAT3(diff.x, diff.y, diff.z);//top
	data.uv[20] = XMFLOAT2(1, 1);
	data.vertices[21] = XMFLOAT3(0, diff.y, 0); //top
	data.uv[21] = XMFLOAT2(5 / 6.f, 0);
	data.vertices[22] = XMFLOAT3(0, diff.y, diff.z);//top
	data.uv[22] = XMFLOAT2(5 / 6.f, 1);
	data.vertices[23] = XMFLOAT3(diff.x, diff.y, 0);//top
	data.uv[23] = XMFLOAT2(1, 0);//top

	for (int i = 0; i < 24; i++) {
		XMFLOAT3 hd = XMFLOAT3(diff.x * 0.5f, diff.y * 0.5f, diff.z * 0.5f);
		data.vertices[i] = XMFLOAT3(data.vertices[i].x - hd.x, data.vertices[i].y - hd.y, data.vertices[i].z - hd.z);
	}

	//sides
	//side1
	data.triangles[0] = 2;
	data.triangles[1] = 1;
	data.triangles[2] = 0;
	data.triangles[3] = 1;
	data.triangles[4] = 2;
	data.triangles[5] = 4;
	//side2
	data.triangles[6] = 3;
	data.triangles[7] = 8;
	data.triangles[8] = 9;
	data.triangles[9] = 5;
	data.triangles[10] = 8;
	data.triangles[11] = 3;
	//side3
	data.triangles[12] = 10;
	data.triangles[13] = 6;
	data.triangles[14] = 7;
	data.triangles[15] = 11;
	data.triangles[16] = 6;
	data.triangles[17] = 10;
	//side4
	data.triangles[18] = 12;
	data.triangles[19] = 13;
	data.triangles[20] = 14;
	data.triangles[21] = 14;
	data.triangles[22] = 13;
	data.triangles[23] = 15;
	//bottom
	data.triangles[24] = 16;
	data.triangles[25] = 17;
	data.triangles[26] = 18;
	data.triangles[27] = 19;
	data.triangles[28] = 17;
	data.triangles[29] = 16;
	//top
	data.triangles[30] = 22;
	data.triangles[31] = 20;
	data.triangles[32] = 21;
	data.triangles[33] = 21;
	data.triangles[34] = 20;
	data.triangles[35] = 23;

	return data;
}

BaseObject::BaseObject(const char* Name, const char* ModelPath, WCHAR* MaterialPath, WCHAR* MaterialPath2)
{
	this->Name = Name;

	mDestroyed = false;
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

	mCollisionRadius = 10000.0f;
	mCollisionEnabled = false;
	mHoveringEnabled = false;
	mDrawOBB = false;
	mDrawAABB = false;

	pWorld = 0;
}

// Initialize the object, set stored materials and initialize the model

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

	if (mCollisionEnabled || mDrawOBB) {
		ComputeOBB();
	}

	if (mCollisionEnabled || mDrawAABB) {
		ComputeAABB();
	}

	if (mCollisionEnabled) {
		EnableCollisions(true);
	}
}

bool BaseObject::IsInitialized()
{
	return Initialized;
}

BaseObject::~BaseObject()
{
	if (pModelClass) {
		pModelClass->Shutdown();
		delete pModelClass;
		pModelClass = 0;
	}
}

const char* BaseObject::GetName()
{
	return Name;
}

int BaseObject::GetID() {
	return ID;
}

// this function could be overriden and used to perform custom render operations on this object

void BaseObject::OnInput(InputFrame inputFrame, float DeltaTime)
{
}

void BaseObject::OnRender(float DeltaTime)
{
	
}

void BaseObject::OnCreate()
{

}

void BaseObject::OnDestroy()
{

}

void BaseObject::Destroy()
{
	mDestroyed = true;
}

bool BaseObject::IsDestroyed()
{
	return mDestroyed;
}

bool BaseObject::operator==(BaseObject other)
{
	return ID == other.ID;
}

// Set the model path and initialize or retrieve the cached model object

void BaseObject::SetModelPath(const char* ModelPath) {
	this->pModelPath = ModelPath;

	if (!Initialized) { return; }

	bool CacheContainsModel = pWorld->ModelCache.find(ModelPath) != pWorld->ModelCache.end();
	if (CacheContainsModel) {
		BumpModelClass* pCachedModelClass = pWorld->ModelCache.at(ModelPath);
		pModelClass = pCachedModelClass;

		return;
	}

	pModelClass = new BumpModelClass;

	HRESULT result = pModelClass->Initialize(pD3DClass->GetDevice(), (char*)ModelPath, GetMaterialPath(), GetNormalPath());

	pWorld->ModelCache[ModelPath] = pModelClass;

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

	if (pAngle->z != 0.f) {
		Matrix = XMMatrixMultiply(Matrix, XMMatrixRotationZ(pAngle->z));
	}
	if (pAngle->y != 0.f) {
		Matrix = XMMatrixMultiply(Matrix, XMMatrixRotationY(pAngle->y));
	}
	if (pAngle->x != 0.f) {
		Matrix = XMMatrixMultiply(Matrix, XMMatrixRotationX(pAngle->x));
	}

	return Matrix;
}

XMMATRIX TransformPosition(XMMATRIX* pMatrix, XMFLOAT3* pPosition) {
	XMMATRIX Matrix = *pMatrix;

	Matrix = XMMatrixMultiply(Matrix, XMMatrixTranslation(pPosition->x, pPosition->y, pPosition->z));

	return Matrix;
}

// This recursive function is used to evaluate the world position of an object
// This function is recursive in order to take into account parent object matrices to modify the location of the child object
// This allows for one parent object to have one or more children which move along with it
// Children of a parent can also have their own children
// This is more useful for planet orbits than the city scene

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

// This returns the world matrix of the object, taking into account its parent (if it has one)
XMMATRIX BaseObject::GetWorldMatrix(XMMATRIX origin) {
	
	origin = XMMatrixScaling(pScale->x, pScale->y, pScale->z);
	origin = CalculateWorldPosition(&origin, this, false);

	if (mUseOrientationMatrix) {
		return mOrientationMatrix;
	}

	return origin;
}

void BaseObject::SetScale(float scale) {
	pScale = new XMFLOAT3(scale, scale, scale);
}

void BaseObject::SetAngle(float p, float y, float r) {
	float DegToRad = 0.0174533f;

	pAngle = new XMFLOAT3(p * DegToRad, y * DegToRad, r * DegToRad);
}

XMFLOAT3 BaseObject::GetAngle() {
	float DegToRad = 0.0174533f;

	return XMFLOAT3(pAngle->x / DegToRad, pAngle->y / DegToRad, pAngle->z / DegToRad);
}

// Collision

void BaseObject::EnableCollisions(bool enabled) {
	mCollisionEnabled = enabled;

	if (pWorld != NULL && enabled) {
		ComputeOBB();
		ComputeAABB();

		pCollisionUtil = new CollisionUtils();		
	}
	else {
		if (!mDrawOBB && pOBB != 0) {
			pOBBModel->Shutdown();
			delete pOBBModel;
			delete pOBB;
		}
		if (!mDrawAABB && pAABB != 0) {
			pAABBModel->Shutdown();
			delete pAABBModel;
			delete pAABB;
		}
	}
}

void BaseObject::EnableHovering(bool enabled)
{
	mHoveringEnabled = enabled;
}

bool BaseObject::GetCollisionsEnabled() {
	return mCollisionEnabled;
}

bool BaseObject::GetHoveringEnabled()
{
	return mHoveringEnabled;
}

void BaseObject::ComputeOBB() {
	if (pWorld == NULL) { return; }

	if (pOBB != 0) {
		delete pOBB;
	}

	if (pOBBModel != 0) {
		pOBBModel->Shutdown();
		delete pOBBModel;
	}

	int vertexCount = pModelClass->GetVertexCount();

	XMFLOAT3* pMins = new XMFLOAT3(99999999,99999999, 99999999);
	XMFLOAT3* pMaxs = new XMFLOAT3(-99999999,-99999999,-99999999);

	for (int i = 0; i < vertexCount; i++) {
		ModelType* pModel = (ModelType*)(pModelClass->m_model + i);

		pMins->x = min(pModel->x, pMins->x);
		pMins->y = min(pModel->y, pMins->y);
		pMins->z = min(pModel->z, pMins->z);

		pMaxs->x = max(pModel->x, pMaxs->x);
		pMaxs->y = max(pModel->y, pMaxs->y);
		pMaxs->z = max(pModel->z, pMaxs->z);
	}
	

	pOBB = new BoundingBox(pMins, pMaxs);

	pOBBModel = new BumpModelClass;
	VertexData data = VerticesFromBoundingBox(pOBB);

	pOBBModel->InitializeFromVertexArray(pWorld->pGraphicsClass->m_D3D->GetDevice(), data, L"../Engine/data/white.dds");
}

void BaseObject::ComputeAABB()
{
	if (pWorld == NULL) { return; }

	if (pOBB == 0) {
		ComputeOBB();
	}

	if (pAABB != 0) {
		delete pAABB;
	}

	if (pAABBModel != 0) {
		pAABBModel->Shutdown();
		delete pAABBModel;
	}

	// pAABBModel = new BumpModelClass;

	XMFLOAT3* pMins = new XMFLOAT3(99999999, 99999999, 99999999);
	XMFLOAT3* pMaxs = new XMFLOAT3(-99999999, -99999999, -99999999);


	// Calculate the min bounds translated
	// Create a scaled and rotated matrix of our object
	XMMATRIX objectMatrix = XMMatrixScaling(pScale->x, pScale->y, pScale->z);
	TransformRotation(&objectMatrix, pAngle);

	// Rather than translate by the object position, translate by the position of the vertex
	XMMATRIX translateMatrix = XMMatrixTranslation(pOBB->pMins->x, pOBB->pMins->y, pOBB->pMins->z);
	objectMatrix = XMMatrixMultiply(objectMatrix, translateMatrix);

	XMVECTOR minVecTranslated = objectMatrix.r[3];


	// Calculate the max bounds translated
	objectMatrix = XMMatrixScaling(pScale->x, pScale->y, pScale->z);
	TransformRotation(&objectMatrix, pAngle);

	translateMatrix = XMMatrixTranslation(pOBB->pMaxs->x, pOBB->pMaxs->y, pOBB->pMaxs->z);
	objectMatrix = XMMatrixMultiply(objectMatrix, translateMatrix);

	XMVECTOR maxVecTranslated = objectMatrix.r[3];

	XMFLOAT3 minFloat;
	XMStoreFloat3(&minFloat, minVecTranslated);
	XMFLOAT3 maxFloat;
	XMStoreFloat3(&maxFloat, maxVecTranslated);

	// Calculate the mins and maxs of the AABB
	pMins->x = min(minFloat.x, maxFloat.x);
	pMins->y = min(minFloat.y, maxFloat.y);
	pMins->z = min(minFloat.z, maxFloat.z);

	pMaxs->x = max(minFloat.x, maxFloat.x);
	pMaxs->y = max(minFloat.y, maxFloat.y);
	pMaxs->z = max(minFloat.z, maxFloat.z);

	pAABB = new BoundingBox(pMins, pMaxs);
}

void BaseObject::DoClick() {

}

void BaseObject::DoHoverStart()
{
}

void BaseObject::DoHoverEnd()
{
}

bool BaseObject::IsHovered()
{
	return mHovered;
}

void BaseObject::SetHovered(bool hovered)
{
	if (hovered != mHovered) {
		if (hovered) {
			DoHoverStart();
		}
		else {
			DoHoverEnd();
		}
	}
	
	mHovered = hovered;
}

bool BaseObject::GetDrawOBB()
{
	return mDrawOBB;
}

bool BaseObject::GetDrawAABB()
{
	return mDrawAABB;
}

void BaseObject::SetDrawOBB(bool draw)
{
	mDrawOBB = draw;

	if (draw) {
		ComputeOBB();
	}
}

void BaseObject::SetDrawAABB(bool draw)
{
	mDrawAABB = draw;

	if (draw) {
		ComputeAABB();
	}
}
