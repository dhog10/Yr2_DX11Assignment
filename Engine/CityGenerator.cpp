#include "CityGenerator.h"
#include "BaseObject.h"
#include "World.h"

CityGenerator::CityGenerator() {
	pBuildings = new std::vector<CityBuilding>();

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
		25.f,
		3.f,
		-6.f,
		10.f);

	AddBuilding("../Engine/data/city/buildings/rb001.obj",
		L"../Engine/data/white.dds",
		25.f,
		25.f,
		0.0015f,
		-6.f,
		20.f);
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
			}

			float xProgress = RoadSegmentSize;
			float yProgress = RoadSegmentSize;

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

					xProgress += w;

					BaseObject* buildingObject = pWorld->CreateObject<BaseObject>("Building",
						building.Model,
						building.Material,
						L"../Engine/data/white.dds");
					buildingObject->SetScale(building.Scale);
					buildingObject->renderShader = RenderShader::SHADED_NO_BUMP;
					buildingObject->pPosition = new XMFLOAT3(xOrigin + xProgress + building.XOffset, 0.f, yOrigin + building.YOffset);

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