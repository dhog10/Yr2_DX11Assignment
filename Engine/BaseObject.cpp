#include "BaseObject.h"



BaseObject::BaseObject(const char* Name, int ID)
{
	this->Name = Name;
	this->ID = ID;
	Position = new XMFLOAT3();
	Velocity = new XMFLOAT3();
	Angle = new XMFLOAT3();
	AngularVelocity = new XMFLOAT3();
}


BaseObject::~BaseObject()
{
	delete Position;
	delete Velocity;
	delete Angle;
	delete AngularVelocity;
}

const char* BaseObject::GetName()
{
	return Name;
}

int BaseObject::GetID() {
	return ID;
}

void BaseObject::OnRender(float DeltaTime)
{
	Position->x += Velocity->x * DeltaTime;
	Position->y += Velocity->y * DeltaTime;
	Position->z += Velocity->z * DeltaTime;

	Angle->x += AngularVelocity->x * DeltaTime;
	Angle->y += AngularVelocity->y * DeltaTime;
	Angle->z += AngularVelocity->z * DeltaTime;
}

void BaseObject::OnCreate()
{

}

void BaseObject::OnDestroy()
{

}

bool BaseObject::operator==(BaseObject other)
{
	return ID == other.ID;
}