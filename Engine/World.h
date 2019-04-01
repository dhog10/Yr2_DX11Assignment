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
class GraphicsClass;
class ShipSelect;
class Ship;

enum GameState {
	SHIP_SELECT,
	PLAY,
};

class World
{
private:
	std::vector<BaseObject*>* Objects;
	int CurrentID;
	GameState mGameState;
	void StartShipSelect();
	void StartPlay();
	void SpawnShipSelects();
	void RemoveShipSelects();

	std::vector<ShipSelect*> mShipSelects;

	Ship* pPlayerShip;
public:
	World();
	~World();

	void Think();
	int mScore = 0;
	int mHealth = 10;

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

	bool mCameraMovementEnabled;
	XMFLOAT3* pCameraPosition;
	XMFLOAT3* pCameraAngle;
	XMFLOAT3* pLightingOrigin;
	XMFLOAT3* pLightingAngle;
	WCHAR* pSkySphereMaterial;

	GraphicsClass* pGraphicsClass;
	CityGenerator* pCityGenerator;

	void DestroyObject(BaseObject*);
	void SetGameState(GameState state);
	GameState GetGameState();
	enum ShipType mPlayerShipType;
	Ship* GetPlayerShip();
};

