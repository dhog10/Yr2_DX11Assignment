#pragma once

#include "textclass.h"

class GraphicsClass;

namespace Collision {
	enum CollisionDetectionType {
		SPHERE,
	};
}

class CollisionUtils
{
public:
	bool TestIntersection(Collision::CollisionDetectionType detectionType, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, int mouseX, int mouseY);
	bool RaySphereIntersect(XMFLOAT3 rayOrigin, XMFLOAT3 rayDirection, float radius);

	GraphicsClass* pGraphicsClass;
	int m_screenWidth = 0;
	int m_screenHeight = 0;

	TextClass* m_Text;
};