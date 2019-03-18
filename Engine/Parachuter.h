#pragma once

#include "BaseObject.h"

class Parachuter : public BaseObject
{
public:
	Parachuter(const char* Name, const char* ModelPath, WCHAR* MaterialPath, WCHAR* MaterialPath2);
	~Parachuter();

	virtual void DoClick();
};

