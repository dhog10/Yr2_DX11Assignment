#pragma once

////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////


///////////////////////
// MY CLASS INCLUDES //
///////////////////////

#ifndef GCLASS
#define GCLASS

#include "d3dclass.h"
#include "shadermanagerclass.h"
#include "cameraclass.h"
#include "lightclass.h"
#include "modelclass.h"
#include "bumpmodelclass.h"
#include "World.h"

#include "skyplaneclass.h"
#include "skyplaneshaderclass.h"

#endif // !GCLASS



/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 20000.0f;
const float SCREEN_NEAR = 0.1f;


////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND, World*);
	void Shutdown();
	bool Frame();
	XMFLOAT3* pCameraVelocity;
	D3DClass* m_D3D;
	CameraClass* m_Camera;
private:
	bool Render(float);

private:
	
	ShaderManagerClass* m_ShaderManager;
	
	LightClass* m_Light;
	ModelClass* m_Model1;
	ModelClass* m_Model2;
	BumpModelClass* m_Model3;
	World* pWorld;
	POINT lastCursorPos;

	SkyPlaneClass *m_SkyPlane;
	SkyPlaneShaderClass* m_SkyPlaneShader;

	double LastTime;
};