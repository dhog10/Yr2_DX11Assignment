#pragma once

#include "BaseObject.h"
#include <vector>

class World
{
private:
	std::vector<BaseObject>* Objects;
	int CurrentID;
public:
	World();
	~World();

	std::vector<BaseObject>* GetObjects();

	template<class T>
	T* CreateObject(const char* Name);

	void DestroyObject(BaseObject*);
};

