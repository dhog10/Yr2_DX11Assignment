#include "Missile.h"


Missile::Missile(const char * Name, const char * ModelPath, WCHAR * MaterialPath, WCHAR * MaterialPath2) : BaseObject::BaseObject(Name, ModelPath, MaterialPath, MaterialPath2)
{
	SetModelPath("../Engine/data/missile/missile.obj");
	SetMaterialPath(L"../Engine/data/missile/missile.dds");
	pMaterialPath2 = L"../Engine/data/missile/missile.dds";

	mMissileSpeed = 120.f;
}

Missile::~Missile()
{
}

void Missile::OnRender(float deltaTime)
{
	
}

void Missile::DoClick()
{
}
