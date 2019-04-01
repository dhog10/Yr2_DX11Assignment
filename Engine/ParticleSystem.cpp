#include "ParticleSystem.h"
#include "Particle.h"
#include "graphicsclass.h"
#include "bumpmodelclass.h"

ParticleSystem::ParticleSystem()
{
}


ParticleSystem::~ParticleSystem()
{
	delete pModelClass;
}

int ParticleSystem::GetNumParticles()
{
	return mParticles.size();
}

Particle * ParticleSystem::CreateParticle(WCHAR * materialPath)
{
	Particle* pParticle = new Particle();
	pParticle->pParticleSystem = this;
	pParticle->pMaterial = materialPath;
	pParticle->Initialize();

	mParticles.push_back(pParticle);

	return pParticle;
}

void ParticleSystem::Initialize()
{
	pModelClass = new BumpModelClass();
	HRESULT result = pModelClass->Initialize(pD3D->GetDevice(), "../Engine/data/plane.obj", L"../Engine/data/missile/smoke.dds", L"../Engine/data/missile/smoke.dds");
}

void ParticleSystem::RenderParticles(float deltaTime, GraphicsClass* pGraphicsClass, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix)
{
	pD3D->TurnOnAlphaBlending();

	// Iterate in reverse order so we can delete particles during loop
	for (int i = mParticles.size() - 1; i >= 0; i--) {
		Particle* pParticle = mParticles.at(i);

		if (pParticle->mDestroyed) {
			// remove destroyed particles
			mParticles.erase(mParticles.begin() + i);

			delete pParticle;
		}
		else {
			XMMATRIX particleMatrix = pParticle->GetWorldMatrix(worldMatrix, XMFLOAT3(0,0,0));
			
			pModelClass->Render(pD3D->GetDeviceContext());
			pGraphicsClass->m_ShaderManager->RenderTextureShader(pD3D->GetDeviceContext(), pModelClass->GetIndexCount(), particleMatrix, viewMatrix, projectionMatrix,
				pModelClass->GetColorTexture());

			particleMatrix = pParticle->GetWorldMatrix(worldMatrix, XMFLOAT3(90, 0, 0));
			pGraphicsClass->m_ShaderManager->RenderTextureShader(pD3D->GetDeviceContext(), pModelClass->GetIndexCount(), particleMatrix, viewMatrix, projectionMatrix,
				pModelClass->GetColorTexture());

			particleMatrix = pParticle->GetWorldMatrix(worldMatrix, XMFLOAT3(0, 90, 0));
			pGraphicsClass->m_ShaderManager->RenderTextureShader(pD3D->GetDeviceContext(), pModelClass->GetIndexCount(), particleMatrix, viewMatrix, projectionMatrix,
				pModelClass->GetColorTexture());

			pParticle->OnRender(deltaTime);
		}
	}

	pD3D->TurnOffAlphaBlending();
}
