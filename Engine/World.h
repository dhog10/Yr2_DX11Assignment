#pragma once

#include "BaseObject.h"
#include <vector>

class World
{
private:
	std::vector<BaseObject*>* Objects;
	int CurrentID;
public:
	World();
	~World();

	std::vector<BaseObject*>* GetObjects();

	template<class T>
	T* CreateObject(const char* Name, const char* ModelPath, const char* MaterialPath, const char* MaterialPath2);

	void DestroyObject(BaseObject*);
};

