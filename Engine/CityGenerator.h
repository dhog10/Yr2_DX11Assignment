/**
NIEE2211 - Computer Games Studio 2

Filename: CityGenerator.h
Author: Daniel Lush
Date: 13/12/2018
*/

#pragma once
#include "d3dclass.h"
#include "Parachuter.h"
#include <vector>

class World;

class CityBuilding {
public:
	char* Model;
	WCHAR* Material;
	float Width;
	float Height;
	float Scale;
	float XOffset;
	float YOffset;
};

class CityCar {
public:
	char* Model;
	WCHAR* Material;
	float Scale;
	float Yaw;
};

class CityGenerator {
private:
	std::vector<CityCar>* pCarTypes;
	std::vector<class BaseObject*> Cars;
	std::vector<class Parachuter*> Parachuters;

	int MaxCars;
	float LastCarSpawn;
	float lastParachuteSpawn;

	void AddCar(char* model, WCHAR* material, float scale, float yaw);

	// Collisions

	bool BuildingCollisionsEnabled;
	bool LampCollisionsEnabled;
	bool VehicleCollisionsEnabled;
	bool RoadCollisionsEnabled;
public:
	CityGenerator();
	~CityGenerator();

	void Think(World*);

	std::vector<CityBuilding>* pBuildings;

	char* StraightRoadModel;
	WCHAR* StraightRoadMaterial;
	char* CrossRoadsModel;
	WCHAR* CrossRoadsMaterial;
	char* LampModel;
	WCHAR* LampMaterial;

	float RoadSegmentSize;
	float RoadSegmentScale;
	int RoadLength;
	int NumRoads;

	void GenerateWorld(World* pWorld);
	void AddBuilding(char* model, WCHAR* material, float width, float height, float scale, float XOffset, float YOffset);

	// Collisions
	bool GetBuildingCollisionsEnabled();
	bool GetLampCollisionsEnabled();
	bool GetVehicleCollisionsEnabled();
	bool GetRoadCollisionsEnabled();
};