#pragma once

/**
Filename: World.h
Author: Daniel Lush
Date: 13/12/2018
*/

#include <vector>
#include <map>
#include "CityGenerator.h"

class BaseObject;

class World
{
private:
	std::vector<BaseObject*>* Objects;
	int CurrentID;
public:
	World();
	~World();

	void Think();
	int mScore = 0;

	std::map<const char*, BumpModelClass*> ModelCache;


	std::vector<BaseObject*>* GetObjects();

	template<class T>
	T* CreateObject(const char* Name, const char* ModelPath, WCHAR* MaterialPath, WCHAR* MaterialPath2) {
		T* pObject = new T(Name, ModelPath, MaterialPath, MaterialPath2);
		pObject->ID = CurrentID;
		pObject->pWorld = this;
		CurrentID++;

		// Add to object array & call create functions
		Objects->push_back((BaseObject*)pObject);

		pObject->OnCreate();

		return pObject;
	}

	XMFLOAT3* pCameraPosition;
	XMFLOAT3* pCameraAngle;
	XMFLOAT3* pLightingOrigin;
	XMFLOAT3* pLightingAngle;
	WCHAR* pSkySphereMaterial;

	CityGenerator* pCityGenerator;

	void DestroyObject(BaseObject*);
};

