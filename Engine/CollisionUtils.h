#pragma once


#include "textclass.h"
#include "graphicsclass.h"


class CollisionUtils
{
public:
	void TestIntersection(int mouseX, int mouseY);
	bool RaySphereIntersect(XMFLOAT3 rayOrigin, XMFLOAT3 rayDirection, float radius);

	GraphicsClass* pGraphicsClass;
	int m_screenWidth = 0;
	int m_screenHeight = 0;

	TextClass* m_Text;
};