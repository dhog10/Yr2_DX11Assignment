#pragma once
#include "d3dclass.h"
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

class CityGenerator {
private:
	
public:
	CityGenerator();
	~CityGenerator();

	std::vector<CityBuilding>* pBuildings;

	char* StraightRoadModel;
	WCHAR* StraightRoadMaterial;
	char* CrossRoadsModel;
	WCHAR* CrossRoadsMaterial;

	float RoadSegmentSize;
	float RoadSegmentScale;
	int RoadLength;
	int NumRoads;

	void GenerateWorld(World* pWorld);
	void AddBuilding(char* model, WCHAR* material, float width, float height, float scale, float XOffset, float YOffset);
};