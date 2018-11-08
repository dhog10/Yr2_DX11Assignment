#include "World.h"



World::World()
{
	CurrentID = 0;
	Objects = new std::vector<BaseObject*>();

	BaseObject* TestObject = CreateObject<BaseObject>("Test Object", "../Engine/data/cube.txt", "../Engine/data/stone.dds", "../Engine/data/normal.dds");
	TestObject->pPosition = new XMFLOAT3(0, 30, 100);
	TestObject->pVelocity->x = 3.f;

	BaseObject* TestChild = CreateObject<BaseObject>("Test Child", "../Engine/data/cube.txt", "../Engine/data/stone.dds", "../Engine/data/normal.dds");
	TestChild->pPosition = new XMFLOAT3(0, 5, 0);
	TestChild->SetParent(TestObject);
	TestChild->pAngularVelocity = new XMFLOAT3(0, 0, 2);
	TestChild->bRotateFirst = false;

	BaseObject* TestChild2 = CreateObject<BaseObject>("Test Child 2", "../Engine/data/cube.txt", "../Engine/data/stone.dds", "../Engine/data/normal.dds");
	TestChild2->pPosition = new XMFLOAT3(0, 3, 0);
	TestChild2->SetParent(TestChild);
	TestChild2->pAngularVelocity = new XMFLOAT3(0, 5, 0);
	TestChild2->bRotateFirst = false;
}


World::~World()
{
	delete Objects;
}

std::vector<BaseObject*>* World::GetObjects()
{
	return Objects;
}

template<class T>
T* World::CreateObject(const char* Name, const char* ModelPath, const char* MaterialPath, const char* MaterialPath2)
{
	T* pObject = new T(Name, CurrentID, ModelPath, MaterialPath, MaterialPath2);
	CurrentID++;

	// Add to object array & call create functions
	Objects->push_back((BaseObject*)pObject);

	pObject->OnCreate();

	return pObject;
}

void World::DestroyObject(BaseObject* pObject)
{
	// Remove from object array & call destroy functions
	std::vector<BaseObject*>::iterator index = std::find(Objects->begin(), Objects->end(), pObject);
	if (index != Objects->end()) {
		Objects->erase(index);
	}

	pObject->OnDestroy();

	delete pObject;
}