#pragma once

#include "d3dclass.h"

class BaseObject
{
private:
	const char* Name;
	int ID;
public:
	BaseObject(const char* Name, int ID);
	~BaseObject();

	const char* ModelPath;
	const char* MaterialPath;

	const char* GetName();
	int GetID();

	XMFLOAT3 * Position;
	XMFLOAT3 * Velocity;
	XMFLOAT3 * Angle;
	XMFLOAT3 * AngularVelocity;

	void OnRender(float);
	void OnCreate();
	void OnDestroy();

	bool operator==(BaseObject other);
};

