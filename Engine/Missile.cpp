#include "Missile.h"


Missile::Missile(const char * Name, const char * ModelPath, WCHAR * MaterialPath, WCHAR * MaterialPath2) : BaseObject::BaseObject(Name, ModelPath, MaterialPath, MaterialPath2)
{

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
