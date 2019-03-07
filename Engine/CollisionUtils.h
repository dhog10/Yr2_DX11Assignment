#pragma once
static class CollisionUtils
{
public:
	static void PickRayVector(float mouseX, float mouseY, XMVECTOR& pickRayInWorldSpacePos, XMVECTOR& pickRayInWorldSpaceDir, int ScrWidth, int ScrHeight);
};

