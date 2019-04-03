/**
NIEE2211 - Computer Games Studio 2

Filename: CityGenerator.cpp
Author: Daniel Lush
Date: 13/12/2018
*/

#include "BaseObject.h"
#include "World.h"
#include "Parachuter.h"
#include "CityGenerator.h"

CityGenerator::CityGenerator() {
	pBuildings = new std::vector<CityBuilding>();
	pCarTypes = new std::vector<CityCar>();
	Cars = std::vector<BaseObject*>();
	Parachuters = std::vector<Parachuter*>();

	MaxCars = 100;
	LastCarSpawn = 0.f;
	LampModel = "../Engine/data/city/lamp.obj";
	LampMaterial = L"../Engine/data/white.dds";

	BuildingRenderOBB = false;
	BuildingRenderAABB = true;
	BuildingCollisionsEnabled = true;
	LampCollisionsEnabled = false;
	VehicleCollisionsEnabled = false;
	RoadCollisionsEnabled = false;

	// Initialize building types

	AddBuilding("../Engine/data/city/buildings/building_1.obj",
		L"../Engine/data/city/buildings/building_1.dds",
		40.f,	// Width
		20.f,	// Height
		0.003f,	// Scale
		-20.f,	//XOffset
		10.f);	// YOffset

	AddBuilding("../Engine/data/city/buildings/247_house.obj",
		L"../Engine/data/white.dds",
		15.f,
		15.f,
		0.04f,
		-6.f,
		10.f);

	AddBuilding("../Engine/data/city/buildings/building.obj",
		L"../Engine/data/white.dds",
		25.f,
		28.f,
		3.f,
		-6.f,
		10.f);

	AddBuilding("../Engine/data/building/building1.obj",
		L"../Engine/data/white.dds",
		50.f,
		50.f,
		5.f,
		-20.f,
		24.f);

	AddBuilding("../Engine/data/building/building2.obj",
		L"../Engine/data/white.dds",
		60.f,
		50.f,
		7.f,
		-30.f,
		15.f);

	AddBuilding("../Engine/data/building/building3.obj",
		L"../Engine/data/white.dds",
		70.f,
		50.f,
		7.f,
		-25.f,
		20.f);

	AddBuilding("../Engine/data/city/buildings/rb001.obj",
		L"../Engine/data/white.dds",
		25.f,
		40.f,
		0.0015f,
		-6.f,
		20.f);

	/*AddBuilding("../Engine/data/city/buildings/scifi/b1.obj",
		L"../Engine/data/city/buildings/scifi/glass.dds",
		40.f,
		40.f,
		0.3f,
		0.f,
		20.f);

	AddBuilding("../Engine/data/city/buildings/scifi/b2.obj",
		L"../Engine/data/city/buildings/scifi/glass.dds",
		40.f,
		40.f,
		0.3f,
		0.f,
		20.f);

	AddBuilding("../Engine/data/city/buildings/scifi/b3.obj",
		L"../Engine/data/city/buildings/scifi/glass.dds",
		40.f,
		40.f,
		0.3f,
		0.f,
		20.f);

	AddBuilding("../Engine/data/city/buildings/scifi/b4.obj",
		L"../Engine/data/city/buildings/scifi/glass.dds",
		40.f,
		40.f,
		0.3f,
		0.f,
		20.f);

	AddBuilding("../Engine/data/city/buildings/scifi/b5.obj",
		L"../Engine/data/city/buildings/scifi/glass.dds",
		40.f,
		40.f,
		0.3f,
		0.f,
		20.f);

	AddBuilding("../Engine/data/city/buildings/scifi/b6.obj",
		L"../Engine/data/city/buildings/scifi/glass.dds",
		40.f,
		40.f,
		0.3f,
		0.f,
		20.f);

	AddBuilding("../Engine/data/city/buildings/scifi/b7.obj",
		L"../Engine/data/city/buildings/scifi/glass.dds",
		40.f,
		40.f,
		0.3f,
		0.f,
		20.f);

	AddBuilding("../Engine/data/city/buildings/scifi/b8.obj",
		L"../Engine/data/city/buildings/scifi/glass.dds",
		40.f,
		40.f,
		0.3f,
		0.f,
		20.f);

	AddBuilding("../Engine/data/city/buildings/scifi/b9.obj",
		L"../Engine/data/city/buildings/scifi/glass.dds",
		40.f,
		40.f,
		0.3f,
		0.f,
		20.f);

	AddBuilding("../Engine/data/city/buildings/scifi/b10.obj",
		L"../Engine/data/city/buildings/scifi/glass.dds",
		40.f,
		40.f,
		0.3f,
		0.f,
		20.f);*/

	// Initialize car types

	AddCar("../Engine/data/cars/police_car.obj", // Model
		L"../Engine/data/white.dds",			 // Material
		3.0f,									 // Scale
		90.f);									 // Yaw

	AddCar("../Engine/data/cars/car1.obj",
		L"../Engine/data/white.dds",
		3.0f,
		90.f);

	AddCar("../Engine/data/cars/limo.obj",
		L"../Engine/data/white.dds",
		3.0f,
		90.f);
}

CityGenerator::~CityGenerator() {

}

void CityGenerator::GenerateWorld(World* pWorld) {
	RenderShader roadShader = RenderShader::SHADED_NO_BUMP;
	RenderShader buildingShader = RenderShader::SHADED_NO_BUMP;

	for (int x = 0; x < NumRoads; x++) {
		for (int y = 0; y < NumRoads; y++) {
			float xOrigin = RoadSegmentSize * RoadLength * x;
			float yOrigin = RoadSegmentSize * RoadLength * y;

			// Create corner junction roads
			BaseObject* roadJunction = pWorld->CreateObject<BaseObject>("Cross Road",
				CrossRoadsModel,
				CrossRoadsMaterial,
				L"../Engine/data/white.dds");
			roadJunction->SetScale(RoadSegmentScale);
			roadJunction->pPosition = new XMFLOAT3(xOrigin, 0.f, yOrigin);
			roadJunction->renderShader = roadShader;

			if (GetRoadCollisionsEnabled()) {
				roadJunction->EnableCollisions(true);
			}

			// Create straight roads & buildings
			for (int i = 1; i < RoadLength; i++) {
				BaseObject* roadHorizontal = pWorld->CreateObject<BaseObject>("Vertical Road",
					StraightRoadModel,
					StraightRoadMaterial,
					L"../Engine/data/white.dds");
				roadHorizontal->SetScale(RoadSegmentScale);
				roadHorizontal->pPosition = new XMFLOAT3(xOrigin + (RoadSegmentSize * i), 0.f, yOrigin);
				roadHorizontal->renderShader = roadShader;

				BaseObject* roadVertical = pWorld->CreateObject<BaseObject>("Vertical Vertical",
					StraightRoadModel,
					StraightRoadMaterial,
					L"../Engine/data/white.dds");
				roadVertical->SetAngle(0.f, -90.f, 0.f);
				roadVertical->bRotateFirst = true;
				roadVertical->SetScale(RoadSegmentScale);
				roadVertical->pPosition = new XMFLOAT3(xOrigin, 0.f, yOrigin + (RoadSegmentSize * (i - 1)));
				roadVertical->renderShader = roadShader;

				if (GetRoadCollisionsEnabled()) {
					roadHorizontal->EnableCollisions(true);
					roadVertical->EnableCollisions(true);
				}

				// Vertical lamp posts
				BaseObject* lamp = pWorld->CreateObject<BaseObject>("Vertical Vertical",
					LampModel,
					LampMaterial,
					L"../Engine/data/white.dds");
				lamp->SetAngle(0.f, -90.f, 0.f);
				lamp->bRotateFirst = true;
				lamp->SetScale(.1f);
				lamp->pPosition = new XMFLOAT3(xOrigin + 1.f, 0.7f, yOrigin + (RoadSegmentSize * (i - 1)));
				lamp->renderShader = roadShader;

				BaseObject* lamp2 = pWorld->CreateObject<BaseObject>("Vertical Vertical",
					LampModel,
					LampMaterial,
					L"../Engine/data/white.dds");
				lamp2->SetAngle(0.f, 90.f, 0.f);
				lamp2->bRotateFirst = true;
				lamp2->SetScale(.1f);
				lamp2->pPosition = new XMFLOAT3(xOrigin + RoadSegmentSize - 1.f, 0.7f, yOrigin + (RoadSegmentSize * (i - 1)));
				lamp2->renderShader = roadShader;

				// Horizontal lamp posts

				BaseObject* lamp3 = pWorld->CreateObject<BaseObject>("Vertical Vertical",
					LampModel,
					LampMaterial,
					L"../Engine/data/white.dds");
				lamp3->SetAngle(0.f, 180.f, 0.f);
				lamp3->bRotateFirst = true;
				lamp3->SetScale(.1f);
				lamp3->pPosition = new XMFLOAT3(xOrigin + (RoadSegmentSize * (i - 1)), 0.7f, yOrigin - RoadSegmentSize + 1.f);
				lamp3->renderShader = roadShader;

				BaseObject* lamp4 = pWorld->CreateObject<BaseObject>("Vertical Vertical",
					LampModel,
					LampMaterial,
					L"../Engine/data/white.dds");
				lamp4->bRotateFirst = true;
				lamp4->SetScale(.1f);
				lamp4->pPosition = new XMFLOAT3(xOrigin + (RoadSegmentSize * (i - 1)), 0.7f, yOrigin - 1.f);
				lamp4->renderShader = roadShader;

				if (GetLampCollisionsEnabled()) {
					lamp->EnableCollisions(true);
					lamp2->EnableCollisions(true);
					lamp3->EnableCollisions(true);
					lamp4->EnableCollisions(true);
				}
			}

			// Generate randomly distrubuted buildings across the bottom row
			float xProgress = RoadSegmentSize;
			float yProgress = 0.f;
			float yProgress2 = 0.f;
			float yMaxProgress = 0.f;
			float yMaxProgress2 = 0.f;

			if (pBuildings->size() > 0) {
				int c = 0;

				while (xProgress < RoadSegmentSize * RoadLength) {
					CityBuilding building;

					bool found = false;
					for (int i = 0; i < 10; i++) {
						int index = rand() % pBuildings->size();
						if (index > pBuildings->size()) { index = pBuildings->size(); }
						building = pBuildings->at(index); //TODO: Pick random building

						if (xProgress + building.Width <= RoadSegmentSize * RoadLength) {
							found = true;
							break;
						}
					}

					if (!found) { break; }

					float w = building.Width;
					float h = building.Height;

					if (c == 0) {
						yProgress = h;
					}

					yProgress2 = h;

					xProgress += w;

					BaseObject* buildingObject = pWorld->CreateObject<BaseObject>("Building",
						building.Model,
						building.Material,
						L"../Engine/data/white.dds");
					buildingObject->SetScale(building.Scale);
					buildingObject->renderShader = buildingShader;
					buildingObject->pPosition = new XMFLOAT3(xOrigin + xProgress + building.XOffset, 0.f, yOrigin + building.YOffset);
					buildingObject->mStatic = true;

					if (GetBuildingCollisionsEnabled()) {
						buildingObject->EnableCollisions(true);
					}

					if (BuildingRenderAABB) {
						buildingObject->SetDrawAABB(true);
					}

					if (BuildingRenderOBB) {
						buildingObject->SetDrawOBB(true);
					}

					c++;
				}
			}

			// Generate buildings for the top row
			xProgress = RoadSegmentSize;

			if (pBuildings->size() > 0) {
				int c = 0;

				while (xProgress < RoadSegmentSize * RoadLength) {
					CityBuilding building;

					bool found = false;
					for (int i = 0; i < 10; i++) {
						int index = rand() % pBuildings->size();
						if (index > pBuildings->size()) { index = pBuildings->size(); }
						building = pBuildings->at(index); //TODO: Pick random building

						if (xProgress + building.Width <= RoadSegmentSize * RoadLength) {
							found = true;
							break;
						}
					}

					if (!found) { break; }

					float w = building.Width;
					float h = building.Height;

					if (c == 0) {
						yMaxProgress = h;
					}

					yMaxProgress2 = h;

					xProgress += w;

					BaseObject* buildingObject = pWorld->CreateObject<BaseObject>("Building",
						building.Model,
						building.Material,
						L"../Engine/data/white.dds");
					buildingObject->SetScale(building.Scale);
					buildingObject->renderShader = buildingShader;
					buildingObject->pPosition = new XMFLOAT3(xOrigin + xProgress + building.XOffset, 0.f, yOrigin - building.YOffset + (RoadSegmentSize * (RoadLength - 1)));
					buildingObject->SetAngle(0.f, 180.f, 0.f);
					buildingObject->mStatic = true;
					
					if (GetBuildingCollisionsEnabled()) {
						buildingObject->EnableCollisions(true);
					}

					if (BuildingRenderAABB) {
						buildingObject->SetDrawAABB(true);
					}

					if (BuildingRenderOBB) {
						buildingObject->SetDrawOBB(true);
					}

					c++;
				}
			}

			xProgress = yProgress;

			// Generate buildings for the left road
			if (pBuildings->size() > 0) {
				int c = 0;

				while (xProgress < (RoadSegmentSize * (RoadLength - 1)) - yMaxProgress) {
					CityBuilding building;

					bool found = false;
					for (int i = 0; i < 10; i++) {
						int index = rand() % pBuildings->size();
						if (index > pBuildings->size()) { index = pBuildings->size(); }
						building = pBuildings->at(index); //TODO: Pick random building

						if (xProgress + building.Width <= (RoadSegmentSize * (RoadLength - 1)) - yMaxProgress) {
							found = true;
							break;
						}
					}

					if (!found) { break; }

					float w = building.Width;
					float h = building.Height;

					xProgress += w;

					BaseObject* buildingObject = pWorld->CreateObject<BaseObject>("Building",
						building.Model,
						building.Material,
						L"../Engine/data/white.dds");
					buildingObject->SetScale(building.Scale);
					buildingObject->renderShader = buildingShader;
					buildingObject->pPosition = new XMFLOAT3(xOrigin + building.YOffset + RoadSegmentSize, 0.f, yOrigin + xProgress + building.XOffset);
					buildingObject->SetAngle(0.f, 90.f, 0.f);
					buildingObject->mStatic = true;

					if (GetBuildingCollisionsEnabled()) {
						buildingObject->EnableCollisions(true);
					}

					if (BuildingRenderAABB) {
						buildingObject->SetDrawAABB(true);
					}

					if (BuildingRenderOBB) {
						buildingObject->SetDrawOBB(true);
					}

					int maxX = RoadSegmentSize * RoadLength * NumRoads;
					int maxY = RoadSegmentSize * RoadLength * NumRoads;

					c++;
				}
			}

			xProgress = yProgress2;

			// Generate buildings for the right road
			if (pBuildings->size() > 0) {
				int c = 0;

				while (xProgress < (RoadSegmentSize * (RoadLength - 1)) - yMaxProgress2) {
					CityBuilding building;

					bool found = false;
					for (int i = 0; i < 10; i++) {
						int index = rand() % pBuildings->size();
						if (index > pBuildings->size()) { index = pBuildings->size(); }
						building = pBuildings->at(index); //TODO: Pick random building

						if (xProgress + building.Width <= (RoadSegmentSize * (RoadLength - 1)) - yMaxProgress2) {
							found = true;
							break;
						}
					}

					if (!found) { break; }

					float w = building.Width;
					float h = building.Height;

					xProgress += w;

					BaseObject* buildingObject = pWorld->CreateObject<BaseObject>("Building",
						building.Model,
						building.Material,
						L"../Engine/data/white.dds");
					buildingObject->SetScale(building.Scale);
					buildingObject->renderShader = buildingShader;
					buildingObject->pPosition = new XMFLOAT3(xOrigin - building.YOffset + (RoadSegmentSize * RoadLength), 0.f, yOrigin + xProgress + building.XOffset);
					buildingObject->SetAngle(0.f, -90.f, 0.f);
					buildingObject->mStatic = true;

					if (GetBuildingCollisionsEnabled()) {
						buildingObject->EnableCollisions(true);
					}

					if (BuildingRenderAABB) {
						buildingObject->SetDrawAABB(true);
					}

					if (BuildingRenderOBB) {
						buildingObject->SetDrawOBB(true);
					}

					c++;
				}
			}
		}
	}
}

void CityGenerator::AddBuilding(char* model, WCHAR* material, float width, float height, float scale, float XOffset, float YOffset) {
	CityBuilding building;
	building.Model = model;
	building.Material = material;
	building.Width = width;
	building.Height = height;
	building.Scale = scale;
	building.XOffset = XOffset;
	building.YOffset = YOffset;

	pBuildings->push_back(building);
}

void CityGenerator::AddCar(char* model, WCHAR* material, float scale, float yaw) {
	CityCar carType;
	carType.Model = model;
	carType.Material = material;
	carType.Scale = scale;
	carType.Yaw = yaw;

	this->pCarTypes->push_back(carType);
}

void CityGenerator::Think(World* pWorld) {
	if (this->pCarTypes->size() == 0) { return; }
	if (!mActive) { return; }

	float time = timeGetTime();

	if (pWorld->GetGameState() == GameState::PLAY && time > lastParachuteSpawn + 1000) {
		lastParachuteSpawn = time;

		Parachuter* parachuter = pWorld->CreateObject<Parachuter>("Parachuter",
			"../Engine/data/parachute.obj",
			L"../Engine/data/white.dds",
			L"../Engine/data/white.dds");
		parachuter->renderShader = RenderShader::SHADED_NO_BUMP;
		parachuter->pVelocity = new XMFLOAT3(0, -15, 0);
		parachuter->EnableCollisions(true);

		int parachuteX = rand() % (int)RoadSegmentSize * RoadLength * NumRoads;
		int parachuteY = 500 + (rand() % 120);
		int parachuteZ = rand() % (int)RoadSegmentSize * RoadLength * NumRoads;

		parachuter->pPosition = new XMFLOAT3(parachuteX, parachuteY, parachuteZ);
		
		int yaw = rand() & 360;
		parachuter->SetAngle(0.f, (float)yaw, 0.f);

		float yawVel = (rand() & 2);
		yawVel *= 0.1f;
		parachuter->pAngularVelocity = new XMFLOAT3(0.f, (float)yawVel, 0.f);
	}

	if (time < LastCarSpawn + 1000) { return; }
	LastCarSpawn = time;

	if (this->pCarTypes->size() < this->MaxCars) {
		for (int x = 0; x < NumRoads; x++) {
			for (int y = 0; y < NumRoads; y++) {
				if (x != 0 && y != 0) { continue; }

				float xOrigin = RoadSegmentSize * RoadLength * x;
				float yOrigin = (RoadSegmentSize * RoadLength * y) - RoadSegmentSize;

				if (rand() % 20 <= 2) {
					// Pick a random car type to spawn
					int index = rand() % pCarTypes->size();
					if (index > pCarTypes->size()) { index = pCarTypes->size(); }
					CityCar carType = pCarTypes->at(index);

					BaseObject* carObject = pWorld->CreateObject<BaseObject>("Car",
						carType.Model,
						carType.Material,
						L"../Engine/data/white.dds");
					carObject->SetScale(carType.Scale);
					carObject->renderShader = RenderShader::SHADED_NO_BUMP;

					float laneCenter = RoadSegmentSize * 0.5f;
					float laneOffset = 5.f;
					float carHeightOffset = 0.5f;

					if (x > 1) { x = 1; }
					if (y > 1) { y = 1; }

					if (x > 0) {
						carObject->SetAngle(0.f, carType.Yaw - 90.f, 0.f);
					}
					else {
						carObject->SetAngle(0.f, carType.Yaw, 0.f);
					}
					

					if (rand() % 2 == 1) {
						// Spawn car from x,y
						carObject->pPosition = new XMFLOAT3(xOrigin + (x * laneCenter) + (x * laneOffset), carHeightOffset, yOrigin + (y * laneCenter) + (-y * laneOffset));
						carObject->pVelocity = new XMFLOAT3(y * 10.f, 0.f, x * 10.f);
					}
					else {
						// Spawn car from x+width, y+width
						carObject->pPosition = new XMFLOAT3(xOrigin + (x * laneCenter) - (x * laneOffset) + (RoadSegmentSize * RoadLength * y * NumRoads), carHeightOffset, yOrigin + (y * laneCenter) - (-y * laneOffset) + (RoadSegmentSize * RoadLength * x * NumRoads));
						carObject->pVelocity = new XMFLOAT3(-y * 10.f, 0.f, -x * 10.f);
						XMFLOAT3 ang = carObject->GetAngle();
						carObject->SetAngle(0.f, ang.y + 180.f, 0.f);
					}

					Cars.push_back(carObject);
				}
			}
		}
	}

	for (int i = 0; i < Cars.size(); i++) {
		BaseObject* pCar = Cars.at(i);

		float xVel = pCar->pVelocity->x;
		float zVel = pCar->pVelocity->z;
		float xPos = pCar->pPosition->x;
		float zPos = pCar->pPosition->z;
		float max = RoadSegmentSize * RoadLength * NumRoads;

		if (xVel > 0) {
			if (xPos > max) {

			}
		}
		else {
			if (xPos < 0) {

			}
		}

		if (zVel > 0) {
			if (zPos > max) {

			}
		}
		else {
			if (zPos < 0) {

			}
		}

	}
}

// Collisions

bool CityGenerator::GetBuildingCollisionsEnabled() {
	return BuildingCollisionsEnabled;
}

bool CityGenerator::GetLampCollisionsEnabled() {
	return LampCollisionsEnabled;
}

bool CityGenerator::GetVehicleCollisionsEnabled() {
	return VehicleCollisionsEnabled;
}

bool CityGenerator::GetRoadCollisionsEnabled() {
	return RoadCollisionsEnabled;
}