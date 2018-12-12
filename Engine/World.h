#pragma once

#include "BaseObject.h"
#include <vector>
#include <map>

#include "CityGenerator.h"

class World
{
private:
	std::vector<BaseObject*>* Objects;
	int CurrentID;
public:
	World();
	~World();

	void Think();

	std::map<const char*, BumpModelClass*> ModelCache;


	std::vector<BaseObject*>* GetObjects();

	template<class T>
	T* CreateObject(const char* Name, const char* ModelPath, WCHAR* MaterialPath, WCHAR* MaterialPath2);

	XMFLOAT3* pCameraPosition;
	XMFLOAT3* pCameraAngle;
	XMFLOAT3* pLightingOrigin;
	XMFLOAT3* pLightingAngle;
	WCHAR* pSkySphereMaterial;

	CityGenerator* pCityGenerator;

	void DestroyObject(BaseObject*);
};

