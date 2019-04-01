#include "Ship.h"
#include "MathUtil.h"
#include "Missile.h"
#include "World.h"
#include "graphicsclass.h"
#include "ParticleSystem.h"

Ship::Ship(const char* Name, const char* ModelPath, WCHAR* MaterialPath, WCHAR* MaterialPath2) : BaseObject::BaseObject(Name, ModelPath, MaterialPath, MaterialPath2)
{
	mMinSpeed = 35.f;
	mMaxSpeed = 75.f;
	mAcceleration = 15.f;
	SetShipSpeed(45.f);
	SetShipType(ShipType::DEFAULT);
	SetScale(0.1f);
	SetEnemy(true);

	lastCameraPosition = XMFLOAT3(0, 0, 0);
	lastShipDirection = XMFLOAT3(0, 0, 0);
}

Ship::~Ship()
{
}

void Ship::FireMissile(BaseObject * pTarget)
{
	Missile* pMissile = pWorld->CreateObject<Missile>("Missile",
		"",
		L"../Engine/data/white.dds",
		L"../Engine/data/white.dds");

	pMissile->pTarget = pTarget;
	pMissile->pPosition = new XMFLOAT3(pPosition->x, pPosition->y, pPosition->z);
}

void Ship::OnRender(float deltaTime)
{	
	if (mPlayerShip && !mEnemy) {
		XMFLOAT3 camAng = GetAngle();
		XMFLOAT3 direction = MathUtil::AngleDirection(camAng);
		XMFLOAT3 cameraDirection = MathUtil::AngleDirection(*pWorld->pCameraAngle);

		pVelocity = new XMFLOAT3(cameraDirection.y * mSpeed, -cameraDirection.z * mSpeed, cameraDirection.x * mSpeed);

		float cameraBackDistance = 65.f + (mSpeed * 0.4f);
		float cameraUpDistance = 20.f;

		XMFLOAT3 cameraBackDirection = XMFLOAT3(cameraDirection.y, -cameraDirection.z, cameraDirection.x);
		XMFLOAT3 pos = XMFLOAT3(pPosition->x, pPosition->y, pPosition->z);

		XMFLOAT3 cameraPos = MathUtil::AddFloat3(pos, MathUtil::MultiplyFloat3(MathUtil::InvertFloat3(cameraBackDirection), cameraBackDistance));
		cameraPos = MathUtil::AddFloat3(cameraPos, XMFLOAT3(0.f, cameraUpDistance, 0.f));
		lastCameraPosition = MathUtil::AddFloat3(lastCameraPosition, MathUtil::MultiplyFloat3(MathUtil::SubtractFloat3(cameraPos, lastCameraPosition), 0.1f));
		pWorld->pCameraPosition = new XMFLOAT3(lastCameraPosition.x, lastCameraPosition.y, lastCameraPosition.z);
		pWorld->mCameraMovementEnabled = false;


		lastShipDirection = MathUtil::AddFloat3(lastShipDirection, MathUtil::MultiplyFloat3(MathUtil::SubtractFloat3(cameraDirection, lastShipDirection), 0.1f));
		MathUtil::DivideFloat3(lastShipDirection, 180.f);
		XMFLOAT3 newAngle = MathUtil::DirectionAngle(lastShipDirection);
		SetAngle(0.f, -newAngle.z, -newAngle.y);

		std::string text = "\n\nCam Dir: " + std::to_string(cameraDirection.x) + " | " + std::to_string(cameraDirection.y) + " | " + std::to_string(cameraDirection.z)
			+ "\nCam Ang: " + std::to_string(camAng.x) + " | " + std::to_string(camAng.y) + " | " + std::to_string(camAng.z)
			+ "\nDirection: " + std::to_string(direction.x) + "|" + std::to_string(direction.y) + "|" + std::to_string(direction.z)
			+ "\nSpeed: " + std::to_string(mSpeed)
			+ "\n Particles: " + std::to_string(pWorld->pParticleSystem->GetNumParticles());
		pWorld->pGraphicsClass->RenderText(text);
	}
}

void Ship::DoClick()
{
}

void Ship::OnInput(InputFrame inputFrame, float deltaTime)
{
	if (inputFrame.vertical != 0.f) {
		SetShipSpeed(mSpeed + (inputFrame.vertical * deltaTime * mAcceleration));
	}
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

	mShipType = shipType;
}

ShipType Ship::GetShipType()
{
	return mShipType;
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

void Ship::SetShipSpeed(float speed) {
	mSpeed = speed;

	if (mSpeed < mMinSpeed) { mSpeed = mMinSpeed; }
	if (mSpeed > mMaxSpeed) { mSpeed = mMaxSpeed; }
}