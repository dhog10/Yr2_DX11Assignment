 #include "World.h"

#include "Parachuter.h"
#include "StellarBody.h"
#include "BaseObject.h"
#include "Ship.h"
#include "ShipSelect.h"
#include "Missile.h"
#include "graphicsclass.h"
#include "ParticleSystem.h"
/**
	NIEE2211 - Computer Games Studio 2

	Filename: World.cpp
	Author: Daniel Lush
	Date: 13/12/2018
*/

// The world class is responsible for creating and storing game objects
// This class is also used to perform think logic for the city generator

void World::StartShipSelect()
{
	SpawnShipSelects();
	
}

void World::StartPlay()
{
	// Spawn the player ship
	Ship* pPlayerShip = CreateObject<Ship>("Player Ship",
		"",
		L"../Engine/data/white.dds",
		L"../Engine/data/white.dds");
	pPlayerShip->pPosition = new XMFLOAT3(0.f, 140.f, 0.f);
	pPlayerShip->SetAngle(0, -90, 0);
	pPlayerShip->SetEnemy(false);
	pPlayerShip->mPlayerShip = true;
	if (mPlayerShipType) {
		pPlayerShip->SetShipType(mPlayerShipType);
	}

	this->pPlayerShip = pPlayerShip;
}

void World::SpawnShipSelects()
{
	float shipGap = 45.f;
	float selectHeight = 150.f;

	// Spawn ship selects for each ship type
	for (int i = ShipType::DEFAULT; i != ShipType::E; i++)
	{
		ShipType shipType = static_cast<ShipType>(i);

		ShipSelect* pShipSelect = CreateObject<ShipSelect>("Ship Select",
			"",
			L"../Engine/data/white.dds",
			L"../Engine/data/white.dds");
		pShipSelect->SetShipType(shipType);
		pShipSelect->SetEnemy(false);
		pShipSelect->pPosition = new XMFLOAT3(i * shipGap, selectHeight, 0.f);
		pShipSelect->SetAngle(0, 90, 0);
		pShipSelect->mMinSpeed = 0.f;
		pShipSelect->mSpeed = 0.f;

		mShipSelects.push_back(pShipSelect);
	}

	pCameraPosition = new XMFLOAT3(ShipType::E * 0.5f * shipGap, selectHeight + 5.f, -70.f);
}

void World::RemoveShipSelects()
{
	for (int i = 0; i < mShipSelects.size(); i++) {
		mShipSelects.at(i)->Destroy();
	}

	mShipSelects.clear();
}

World::World()
{
	mCameraMovementEnabled = true;
	ModelCache = std::map<const char*, BumpModelClass*>();
	pGraphicsClass = NULL;

	CurrentID = 0;
	Objects = new std::vector<BaseObject*>();
	pLightingOrigin = 0;
	pLightingAngle = new XMFLOAT3(0.6f,-1.f,0.7f); // RIGHT, UP, FRONT

	pCameraPosition = new XMFLOAT3(0.f, 0.f, -10.f);
	pCameraAngle = new XMFLOAT3(0.f, 0.f, 0.f);
	pSkySphereMaterial = L"../Engine/data/skysphere1.dds";

	StellarBody* SkySphere = CreateObject<StellarBody>("Test planet 1", "../Engine/data/sphere_hd.obj", L"../Engine/data/sky/clouds1.dds", L"../Engine/data/sun.dds");
	SkySphere->renderShader = RenderShader::UNLIT;
	SkySphere->pScale = new XMFLOAT3(-500.f, -500.f, -500.f);
	SkySphere->pAngle = new XMFLOAT3(180.f * 0.0174533f, 0.f, 0.f);

	/*StellarBody* Sun = CreateObject<StellarBody>("Test planet 1", "../Engine/data/sphere_hd.obj", L"../Engine/data/sun.dds", L"../Engine/data/sun.dds");
	Sun->pOriginPosition = new XMFLOAT3(0.f, 0, 100.f);
	Sun->bDontTransformParentRotation = true;
	Sun->pAngularVelocity->y = 0.3f;
	Sun->renderShader = RenderShader::UNLIT;

	StellarBody* Earth = CreateObject<StellarBody>("Earth", "../Engine/data/sphere_hd.obj", L"../Engine/data/earth.dds", L"../Engine/data/white.dds");
	Earth->SetParent(Sun);
	Earth->OrbitDistance = 50.f;
	Earth->OrbitSpeed = 5.f;
	Earth->CurrentOrbigDegree = 200.f;
	Earth->pAngularVelocity->y = 0.3f;
	Earth->bDontTransformParentRotation = true;
	Earth->pScale = new XMFLOAT3(0.3f, 0.3f, 0.3f);

	StellarBody* Moon = CreateObject<StellarBody>("Moon", "../Engine/data/sphere_hd.obj", L"../Engine/data/moon.dds", L"../Engine/data/white.dds");
	Moon->SetParent(Earth);
	Moon->OrbitDistance = 25.f;
	Moon->OrbitSpeed = 9.f;
	Moon->CurrentOrbigDegree = 100.f;
	Moon->pAngularVelocity->y = 0.8f;
	Moon->bDontTransformParentRotation = true;
	Moon->pScale = new XMFLOAT3(0.05f, 0.05f, 0.05f);*/

	BaseObject* roadX = CreateObject<BaseObject>("Road X",
		"../Engine/data/city/roads/road_2_lane_x.obj",
		L"../Engine/data/city/roads/road_2_lane_x.dds",
		L"../Engine/data/white.dds");
	roadX->SetScale(0.01f);

	CityGenerator* pGenerator = new CityGenerator();
	pGenerator->RoadSegmentSize = 36.f;
	pGenerator->RoadSegmentScale = 0.01f;
	pGenerator->RoadLength = 10;
	pGenerator->NumRoads = 5;

	pGenerator->StraightRoadModel = "../Engine/data/city/roads/road_2_lane_straight.obj";
	pGenerator->StraightRoadMaterial = L"../Engine/data/city/roads/road_2_lane_straight.dds";
	pGenerator->CrossRoadsModel = "../Engine/data/city/roads/road_2_lane_x.obj";
	pGenerator->CrossRoadsMaterial = L"../Engine/data/city/roads/road_2_lane_x.dds";

	pGenerator->mActive = true;
	pGenerator->GenerateWorld(this);

	this->pCityGenerator = pGenerator;

	mShipSelects = std::vector<ShipSelect*>();
	SetGameState(GameState::SHIP_SELECT);
}


World::~World()
{
	delete Objects;
}

void World::PostInitialized()
{
	pParticleSystem = new ParticleSystem();
	pParticleSystem->pD3D = pGraphicsClass->m_D3D;
	pParticleSystem->Initialize();

	CacheModel("../Engine/data/missile/missile.obj", L"../Engine/data/missile/missile.dds", L"../Engine/data/missile/missile.dds");
}

std::vector<BaseObject*>* World::GetObjects()
{
	return Objects;
}

// Remove an object from the world

void World::DestroyObject(BaseObject* pObject)
{
	// Remove from object array & call destroy functions
	std::vector<BaseObject*>::iterator index = std::find(Objects->begin(), Objects->end(), pObject);
	if (index != Objects->end()) {
		Objects->erase(index);
	}

	pObject->OnDestroy();
}

void World::SetGameState(GameState state)
{
	mGameState = state;

	switch (state) {
	case GameState::SHIP_SELECT:
		StartShipSelect();
		break;
	case GameState::PLAY:
		RemoveShipSelects();
		StartPlay();
		break;
	}
}

GameState World::GetGameState()
{
	return mGameState;
}

Ship* World::GetPlayerShip()
{
	if (pPlayerShip != NULL) {
		return pPlayerShip;
	}
	else {
		return NULL;
	}
}

void World::CacheModel(char * modelFilename, WCHAR * textureFilename1, WCHAR * textureFilename2)
{
	BumpModelClass* pModelClass = new BumpModelClass;
	HRESULT result = pModelClass->Initialize(pGraphicsClass->m_D3D->GetDevice(), modelFilename, textureFilename1, textureFilename2);
	ModelCache[modelFilename] = pModelClass;
}

void World::Think() {
	if (pCityGenerator != 0) {
		pCityGenerator->Think(this);
	}
}