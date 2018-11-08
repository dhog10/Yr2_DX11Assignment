#include "World.h"



World::World()
{
	CurrentID = 0;
	Objects = new std::vector<BaseObject>();

	BaseObject* TestObject = CreateObject<BaseObject>("Test Object");
}


World::~World()
{
	delete Objects;
}

std::vector<BaseObject>* World::GetObjects()
{
	return Objects;
}

template<class T>
T* World::CreateObject(const char* Name)
{
	T* Object = new T(Name, CurrentID);
	CurrentID++;

	// Add to object array & call create functions
	Objects->push_back((BaseObject)*Object);

	Object->OnCreate();

	return Object;
}

void World::DestroyObject(BaseObject* Object)
{
	// Remove from object array & call destroy functions
	std::vector<BaseObject>::iterator index = std::find(Objects->begin(), Objects->end(), *Object);
	if (index != Objects->end()) {
		Objects->erase(index);
	}

	Object->OnDestroy();

	delete Object;
}