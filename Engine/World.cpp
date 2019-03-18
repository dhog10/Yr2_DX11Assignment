 #include "World.h"

#include "Parachuter.h"
#include "StellarBody.h"
#include "BaseObject.h"

/**
	NIEE2211 - Computer Games Studio 2

	Filename: World.cpp
	Author: Daniel Lush
	Date: 13/12/2018
*/

// The world class is responsible for creating and storing game objects
// This class is also used to perform think logic for the city generator

World::World()
{
	ModelCache = std::map<const char*, BumpModelClass*>();

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
	pGenerator->RoadLength = 5;
	pGenerator->NumRoads = 6;

	pGenerator->StraightRoadModel = "../Engine/data/city/roads/road_2_lane_straight.obj";
	pGenerator->StraightRoadMaterial = L"../Engine/data/city/roads/road_2_lane_straight.dds";
	pGenerator->CrossRoadsModel = "../Engine/data/city/roads/road_2_lane_x.obj";
	pGenerator->CrossRoadsMaterial = L"../Engine/data/city/roads/road_2_lane_x.dds";

	pGenerator->GenerateWorld(this);

	this->pCityGenerator = pGenerator;
}


World::~World()
{
	delete Objects;
}

std::vector<BaseObject*>* World::GetObjects()
{
	return Objects;
}

// Create an object, and perform initialization to it

/*template<class T>
T* World::CreateObject(const char* Name, const char* ModelPath, WCHAR* MaterialPath, WCHAR* MaterialPath2)
{
	T* pObject = new T(Name, ModelPath, MaterialPath, MaterialPath2);
	pObject->ID = CurrentID;
	pObject->pWorld = this;
	CurrentID++;

	// Add to object array & call create functions
	Objects->push_back((BaseObject*)pObject);

	pObject->OnCreate();

	return pObject;
}*/

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

void World::Think() {
	if (pCityGenerator != 0) {
		pCityGenerator->Think(this);
	}
}