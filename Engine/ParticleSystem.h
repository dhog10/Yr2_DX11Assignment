#pragma once

#include "d3dclass.h"
#include <vector>

class Particle;
class GraphicsClass;
class BumpModelClass;

class ParticleSystem
{
public:
	ParticleSystem();
	~ParticleSystem();

	int GetNumParticles();
	Particle* CreateParticle(WCHAR* materialPath);
	void Initialize();

	D3DClass* pD3D;
	BumpModelClass* pModelClass;

	void RenderParticles(float deltaTime, GraphicsClass* pGraphicsClass, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix);
private:
	std::vector<Particle*> mParticles;
};

