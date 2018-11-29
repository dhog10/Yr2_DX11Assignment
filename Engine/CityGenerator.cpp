#include "CityGenerator.h"
#include "BaseObject.h"
#include "World.h"

CityGenerator::CityGenerator() {
	pBuildings = new std::vector<CityBuilding>();

	
}

CityGenerator::~CityGenerator() {

}

void CityGenerator::GenerateWorld(World* pWorld) {
	for (int x = 0; x < NumRoads; x++) {
		for (int y = 0; y < NumRoads; y++) {
			float xOrigin = RoadSegmentSize * RoadLength * x;
			float yOrigin = RoadSegmentSize * RoadLength * y;

			// Create corner junction roads
			BaseObject* roadX = pWorld->CreateObject<BaseObject>("Cross Road",
				CrossRoadsModel,
				CrossRoadsMaterial,
				L"../Engine/data/white.dds");
			roadX->SetScale(RoadSegmentScale);
			roadX->pPosition = new XMFLOAT3(xOrigin, 0.f, yOrigin);

			// Create straight roads & buildings
			for (int i = 1; i < RoadLength; i++) {
				BaseObject* roadH = pWorld->CreateObject<BaseObject>("Vertical Road",
					StraightRoadModel,
					StraightRoadMaterial,
					L"../Engine/data/white.dds");
				roadH->SetScale(RoadSegmentScale);
				roadH->pPosition = new XMFLOAT3(xOrigin + (RoadSegmentSize * i), 0.f, yOrigin);

				BaseObject* roadV = pWorld->CreateObject<BaseObject>("Vertical Vertical",
					StraightRoadModel,
					StraightRoadMaterial,
					L"../Engine/data/white.dds");
				roadV->SetAngle(0.f, -90.f, 0.f);
				roadV->bRotateFirst = true;
				roadV->SetScale(RoadSegmentScale);
				roadV->pPosition = new XMFLOAT3(xOrigin, 0.f, yOrigin + (RoadSegmentSize * (i - 1)));

				float xProgress = 0.f;
				float yProgress = 0.f;

				if (pBuildings->size() > 0) {
					while (xProgress < RoadSegmentSize) {
						CityBuilding building = pBuildings->at(0); //TODO: Pick random building

						float w = building.Width;
						float h = building.Height;

						if (i == 1) {
							yProgress = h;
						}

						xProgress += w;

						BaseObject* buildingObject = pWorld->CreateObject<BaseObject>("Building",
							building.Model,
							building.Material,
							L"../Engine/data/white.dds");
						buildingObject->SetScale(RoadSegmentScale);
						buildingObject->pPosition = new XMFLOAT3(xOrigin + (RoadSegmentSize * i) + xProgress, 0.f, yOrigin);
					}
				}
			}
		}
	}
}

void CityGenerator::AddBuilding(char* model, WCHAR* material, float width, float height, float scale) {
	CityBuilding building;
	building.Model = model;
	building.Material = material;
	building.Width = width;
	building.Height = height;
	building.Scale = scale;

	pBuildings->push_back(building);
}