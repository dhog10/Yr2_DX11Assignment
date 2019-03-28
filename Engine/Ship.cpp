#include "Ship.h"
#include "MathUtil.h"
#include "World.h"
#include "graphicsclass.h"

Ship::Ship(const char* Name, const char* ModelPath, WCHAR* MaterialPath, WCHAR* MaterialPath2) : BaseObject::BaseObject(Name, ModelPath, MaterialPath, MaterialPath2)
{
	mSpeed = 10.f;
	SetShipType(ShipType::DEFAULT);
	SetScale(0.1f);
	SetEnemy(true);

	lastCameraPosition = XMFLOAT3(0, 0, 0);
	lastShipDirection = XMFLOAT3(0, 0, 0);
}

Ship::~Ship()
{
}

void Ship::OnRender(float deltaTime)
{	
	XMFLOAT3 camAng = GetAngle();
	XMFLOAT3 direction = MathUtil::AngleDirection(camAng);

	pVelocity = new XMFLOAT3(direction.x * mSpeed, direction.z * mSpeed, -direction.y * mSpeed);

	float cameraBackDistance = 65.f;
	float cameraUpDistance = 20.f;

	XMFLOAT3 cameraBackDirection = XMFLOAT3(direction.x, -direction.z, -direction.y);
	XMFLOAT3 pos = XMFLOAT3(pPosition->x, pPosition->y, pPosition->z);

	XMFLOAT3 cameraPos = MathUtil::AddFloat3(pos, MathUtil::MultiplyFloat3(MathUtil::InvertFloat3(cameraBackDirection), cameraBackDistance));
	cameraPos = MathUtil::AddFloat3(cameraPos, XMFLOAT3(0.f, cameraUpDistance, 0.f));
	lastCameraPosition = MathUtil::AddFloat3(lastCameraPosition, MathUtil::MultiplyFloat3(MathUtil::SubtractFloat3(cameraPos, lastCameraPosition), 0.1f));
	pWorld->pCameraPosition = new XMFLOAT3(lastCameraPosition.x, lastCameraPosition.y, lastCameraPosition.z);
	pWorld->mCameraMovementEnabled = false;

	XMFLOAT3 cameraDirection = MathUtil::AngleDirection(*pWorld->pCameraAngle);
	lastShipDirection = MathUtil::AddFloat3(lastShipDirection, MathUtil::MultiplyFloat3(MathUtil::SubtractFloat3(cameraDirection, lastShipDirection), 0.1f));
	MathUtil::DivideFloat3(lastShipDirection, 180.f);
	XMFLOAT3 newAngle = MathUtil::DirectionAngle(lastShipDirection);
	SetAngle(0.f, -newAngle.z, -newAngle.y);

	std::string text = "\n\nCam Dir: " + std::to_string(cameraDirection.x) + " | " + std::to_string(cameraDirection.y) + " | " + std::to_string(cameraDirection.z)
		+ "\nCam Ang: " + std::to_string(camAng.x) + " | " + std::to_string(camAng.y) + " | " + std::to_string(camAng.z)
		+ "\nDirection: " + std::to_string(direction.x) + "|" + std::to_string(direction.y) + "|" + std::to_string(direction.z);
	pWorld->pGraphicsClass->RenderText(text);
}

void Ship::DoClick()
{
}

void Ship::SetShipType(ShipType shipType)
{
	switch (shipType) {
	case ShipType::DEFAULT:
		SetModelPath("../Engine/data/ships/s1.obj");
		break;
	case ShipType::A:
		SetModelPath("../Engine/data/ships/s2.obj");
		break;
	case ShipType::B:
		SetModelPath("../Engine/data/ships/s3.obj");
		break;
	case ShipType::C:
		SetModelPath("../Engine/data/ships/s4.obj");
		break;
	case ShipType::D:
		SetModelPath("../Engine/data/ships/s5.obj");
		break;
	case ShipType::E:
		SetModelPath("../Engine/data/ships/s6.obj");
		break;
	}
}

void Ship::SetEnemy(bool enemy)
{
	mEnemy = enemy;

	if (enemy) {
		SetMaterialPath(L"../Engine/data/ships/s_red.dds");
	}
	else {
		SetMaterialPath(L"../Engine/data/ships/s_blue.dds");
	}
}
