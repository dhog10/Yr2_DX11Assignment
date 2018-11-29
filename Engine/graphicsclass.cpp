////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"
#include <ctime>
#include <chrono>
#include <cstdint>
#include <conio.h>

GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_ShaderManager = 0;
	m_Light = 0;
	m_Camera = 0;
	m_Model1 = 0;
	m_Model2 = 0;
	m_Model3 = 0;
	pCameraVelocity = new XMFLOAT3(0.f, 0.f, 0.f);

	GetCursorPos(&lastCursorPos);
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd, World* pWorld)
{
	bool result;


	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the shader manager object.
	m_ShaderManager = new ShaderManagerClass;
	if(!m_ShaderManager)
	{
		return false;
	}

	// Initialize the shader manager object.
	result = m_ShaderManager->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the shader manager object.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
	
	// Create the light object.
	m_Light = new LightClass;
	if(!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(0.0f, 0.0f, 1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(64.0f);

	// Create the model object.
	m_Model1 = new ModelClass;
	if(!m_Model1)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Model1->Initialize(m_D3D->GetDevice(), "../Engine/data/donut-tri.txt", L"../Engine/data/metal2.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the first model object.", L"Error", MB_OK);
		return false;
	}

	// Create the second model object.
	m_Model2 = new ModelClass;
	if(!m_Model2)
	{
		return false;
	}

	// Initialize the second model object.
	//result = m_Model2->Initialize(m_D3D->GetDevice(), "../Engine/data/cube-ninjaHead.txt", L"../Engine/data/metal.dds");
	result = m_Model2->Initialize(m_D3D->GetDevice(), "../Engine/data/new-ninjaHead.txt", L"../Engine/data/metal.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the second model object.", L"Error", MB_OK);
		return false;
	}

	// Create the third bump model object for models with normal maps and related vectors.
	m_Model3 = new BumpModelClass;
	if(!m_Model3)
	{
		return false;
	}

	// Initialize the bump model object.
	result = m_Model3->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/stone.dds", 
								  L"../Engine/data/normal.dds");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the third model object.", L"Error", MB_OK);
		return false;
	}

	// Assign private world variable
	this->pWorld = pWorld;

	if (!pWorld) {
		MessageBox(hwnd, L"pWorld class pointer null", L"Error", MB_OK);
		return false;
	}

	std::vector<BaseObject*> objects = *pWorld->GetObjects();
	for (int i = 0; i < objects.size(); i++) {
		BaseObject* pObject = objects[i];

		pObject->Initialize(m_D3D);
	}

	LastTime = timeGetTime();

	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the model objects.
	if(m_Model1)
	{
		m_Model1->Shutdown();
		delete m_Model1;
		m_Model1 = 0;
	}

	if(m_Model2)
	{
		m_Model2->Shutdown();
		delete m_Model2;
		m_Model2 = 0;
	}

	if(m_Model3)
	{
		m_Model3->Shutdown();
		delete m_Model3;
		m_Model3 = 0;
	}

	// Release the light object.
	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the shader manager object.
	if(m_ShaderManager)
	{
		m_ShaderManager->Shutdown();
		delete m_ShaderManager;
		m_ShaderManager = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;
}


bool GraphicsClass::Frame()
{
	bool result;
	static float rotation = 0.0f;


	// Update the rotation variable each frame.
	rotation += (float)XM_PI * 0.005f;
	if(rotation > 360.0f)
	{
		rotation -= 360.0f;
	}
	
	// Render the graphics scene.
	result = Render(rotation);
	if(!result)
	{
		return false;
	}

	return true;
}


bool GraphicsClass::Render(float rotation)
{
	////////////////////
	double CurTime = timeGetTime();
	float DeltaTime = (CurTime - LastTime) / 1000.f;
	LastTime = timeGetTime();

	POINT cursorPos;
	GetCursorPos(&cursorPos);

	int fixedCursorX = 100;
	int fixedCursorY = 100;

	int diffX = cursorPos.x - lastCursorPos.x;
	float diffY = cursorPos.y - lastCursorPos.y;
	SetCursorPos(fixedCursorX, fixedCursorY);
	lastCursorPos.x = fixedCursorX;
	lastCursorPos.y = fixedCursorY;

	if (diffX != 0) {
		pWorld->pCameraAngle->y += diffX * DeltaTime * 4;
	}
	if (diffY != 0) {
		pWorld->pCameraAngle->x += diffY * DeltaTime * 4;
	}
	m_Camera->SetRotation(pWorld->pCameraAngle->x, pWorld->pCameraAngle->y, pWorld->pCameraAngle->z);

	float cameraVelocityDampen = 0.3f;

	pCameraVelocity->x *= pCameraVelocity->x * cameraVelocityDampen;
	pCameraVelocity->y *= pCameraVelocity->y * cameraVelocityDampen;
	pCameraVelocity->z *= pCameraVelocity->z * cameraVelocityDampen;


	// Keyboard input
	if (GetKeyState('W') & 0x8000) { // GetAsyncKeyState(VK_LEFT)
		pCameraVelocity->y += 1.f;
	}
	if (GetKeyState('S') & 0x8000) {
		pCameraVelocity->y -= 1.f;
	}
	if (GetKeyState('A') & 0x8000) {
		pCameraVelocity->x -= 1.f;
	}
	if (GetKeyState('D') & 0x8000) {
		pCameraVelocity->x += 1.f;
	}

	if (pCameraVelocity->y < -1) { pCameraVelocity->y = -1; }
	if (pCameraVelocity->y > 1) { pCameraVelocity->y = 1; }
	if (pCameraVelocity->x < -1) { pCameraVelocity->x = -1; }
	if (pCameraVelocity->x > 1) { pCameraVelocity->x = 1; }

	float degToRad = 0.0174533;

	// Find the up vector
	XMVECTOR up = XMLoadFloat3(new XMFLOAT3(0.f, 1.f, 0.f));
	// Find the camera forward heading
	XMFLOAT3* pCameraHeading = new XMFLOAT3(
		sin(pWorld->pCameraAngle->y * degToRad), 
		-sin(pWorld->pCameraAngle->x * degToRad), 
		cos(pWorld->pCameraAngle->y * degToRad)
	);
	// Normalize the camera forward heading
	float cameraHeadingLen = sqrt((pCameraHeading->x * pCameraHeading->x) + (pCameraHeading->y * pCameraHeading->y) + (pCameraHeading->z * pCameraHeading->z));
	pCameraHeading->x = pCameraHeading->x / cameraHeadingLen;
	pCameraHeading->y = pCameraHeading->y / cameraHeadingLen;
	pCameraHeading->z = pCameraHeading->z / cameraHeadingLen;

	// Load heading to vector
	XMVECTOR cameraForward = XMLoadFloat3(pCameraHeading);
	// Find camera right by cross product with up vector
	XMVECTOR cameraRight = XMVector3Cross(up, cameraForward);
	XMFLOAT3 cameraRightFloat;
	XMStoreFloat3(&cameraRightFloat, cameraRight);
	XMFLOAT3 cameraForwardFloat;
	XMStoreFloat3(&cameraForwardFloat, cameraForward);

	float vel = pCameraVelocity->x;

	pWorld->pCameraPosition->x += cameraRightFloat.x * vel;
	pWorld->pCameraPosition->y += cameraRightFloat.y * vel;
	pWorld->pCameraPosition->z += cameraRightFloat.z * vel;

	vel = pCameraVelocity->y;

	pWorld->pCameraPosition->x += cameraForwardFloat.x * vel;
	pWorld->pCameraPosition->y += cameraForwardFloat.y * vel;
	pWorld->pCameraPosition->z += cameraForwardFloat.z * vel;

	

	m_Camera->SetPosition(pWorld->pCameraPosition->x, pWorld->pCameraPosition->y, pWorld->pCameraPosition->z);

	

	XMMATRIX worldMatrix, worldMatrix2, viewMatrix, projectionMatrix, translateMatrix;
	bool result;


	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.


	if (pWorld) {
		std::vector<BaseObject*> objects = *pWorld->GetObjects();

		for (int i = 0; i < objects.size(); i++) {
			BaseObject* pObject = objects[i];

			BumpModelClass* pModelClass = pObject->pModelClass;
			if (!pModelClass) { continue; }

			objects[i]->pPosition->x += objects[i]->pVelocity->x * DeltaTime;
			objects[i]->pPosition->y += objects[i]->pVelocity->y * DeltaTime;
			objects[i]->pPosition->z += objects[i]->pVelocity->z * DeltaTime;

			objects[i]->pAngle->x += objects[i]->pAngularVelocity->x * DeltaTime;
			objects[i]->pAngle->y += objects[i]->pAngularVelocity->y * DeltaTime;
			objects[i]->pAngle->z += objects[i]->pAngularVelocity->z * DeltaTime;

			objects[i]->OnRender(DeltaTime);

			// Reset worldMatrix to origin
			m_D3D->GetWorldMatrix(worldMatrix);
			m_Camera->GetViewMatrix(viewMatrix);
			m_D3D->GetProjectionMatrix(projectionMatrix);

			// Translate matrix using objects xyz (pyr) angle values
			/*if (object->pAngle->x != 0.f) {
				worldMatrix = XMMatrixRotationX(rotation * object->pAngle->x);
			}
			if (object->pAngle->y != 0.f) {
				worldMatrix = XMMatrixRotationX(rotation * object->pAngle->y);
			}
			if (object->pAngle->z != 0.f) {
				worldMatrix = XMMatrixRotationX(rotation * object->pAngle->z);
			}
			
			// Translate matrix using objects xyz position values
			worldMatrix = XMMatrixTranslation(object->pPosition->x, object->pPosition->y, object->pPosition->z);*/

			worldMatrix = pObject->GetWorldMatrix(worldMatrix);
			
			// Store the global xyz coordinates of the object in an XMFLOAT3
			XMVECTOR worldPos = worldMatrix.r[3];
			XMFLOAT3 objectPos;
			XMStoreFloat3(&objectPos, worldPos);

			// Calculate the relative position between the lighting origin and the object
			XMFLOAT3 relativePosition;

			if (pWorld->pLightingOrigin != 0) {
				XMFLOAT3 lightOrigin = *pWorld->pLightingOrigin;
				relativePosition.x = objectPos.x - lightOrigin.x;
				relativePosition.y = objectPos.y - lightOrigin.y;
				relativePosition.z = objectPos.z - lightOrigin.z;


				// Calculate length of relative lighting vector
				float rLen = sqrt((relativePosition.x * relativePosition.x) + (relativePosition.y * relativePosition.y) + (relativePosition.z * relativePosition.z));

				// Normalize relative lighting direction (this is now the light origin normal vector)
				relativePosition.x = relativePosition.x / rLen;
				relativePosition.y = relativePosition.y / rLen;
				relativePosition.z = relativePosition.z / rLen;
			}
			else {
				relativePosition = *pWorld->pLightingAngle;
			}

			// Render the object to scene

			switch (pObject->renderShader) {
			case RenderShader::SHADED:
				pModelClass->Render(m_D3D->GetDeviceContext());
				result = m_ShaderManager->RenderBumpMapShader(m_D3D->GetDeviceContext(), pModelClass->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
					pModelClass->GetColorTexture(), pModelClass->GetNormalMapTexture(), relativePosition,
					m_Light->GetDiffuseColor());
				break;
			case RenderShader::UNLIT:
				pModelClass->Render(m_D3D->GetDeviceContext());
				result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), pModelClass->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
					pModelClass->GetColorTexture());
				break;
			}

			// Render inverse skysphere

			//m_D3D->GetWorldMatrix(worldMatrix);
			//worldMatrix *= XMMatrixScaling(-100.f, -100.f, -100.f);


		}
	}

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}