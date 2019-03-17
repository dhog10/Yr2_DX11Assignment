#include "CollisionUtils.h"
#include "graphicsclass.h"
#include "d3dclass.h"

bool CollisionUtils::TestIntersection(Collision::CollisionDetectionType detectionType, XMMATRIX worldMatrix, XMMATRIX viewMatrix, XMMATRIX projectionMatrix, int mouseX, int mouseY)
{
	float pointX, pointY;
	XMMATRIX inverseViewMatrix, inverseWorldMatrix;
	XMFLOAT3 direction, origin;
	XMVECTOR rayOrigin, rayDirection;

	bool intersect, result;

	// Move the mouse cursor coordinates into the -1 to +1 range.
	pointX = ((2.0f * (float)mouseX) / (float)m_screenWidth) - 1.0f;
	pointY = (((2.0f * (float)mouseY) / (float)m_screenHeight) - 1.0f) * -1.0f;

	// Adjust the points using the projection matrix to account for the aspect ratio of the viewport.
	XMFLOAT4X4 projection4x4;
	XMStoreFloat4x4(&projection4x4, projectionMatrix);

	pointX = pointX / projection4x4._11;
	pointY = pointY / projection4x4._22;

	// Get the inverse of the view matrix.
	inverseViewMatrix = XMMatrixInverse(NULL, viewMatrix);

	XMFLOAT4X4 view4x4;
	XMStoreFloat4x4(&view4x4, inverseViewMatrix);

	// Calculate the direction of the picking ray in view space.
	direction.x = (pointX * view4x4._11) + (pointY * view4x4._21) + view4x4._31;
	direction.y = (pointX * view4x4._12) + (pointY * view4x4._22) + view4x4._32;
	direction.z = (pointX * view4x4._13) + (pointY * view4x4._23) + view4x4._33;

	// Get the origin of the picking ray which is the position of the camera.
	origin = pGraphicsClass->m_Camera->GetPosition();

	// Now get the inverse of the translated world matrix.
	inverseWorldMatrix = XMMatrixInverse(NULL, worldMatrix);

	// Now transform the ray origin and the ray direction from view space to world space.
	XMVECTOR originVector = XMLoadFloat3(&origin);
	rayOrigin = XMVector3TransformCoord(originVector, inverseWorldMatrix);
	XMVECTOR directionVector = XMLoadFloat3(&direction);
	rayDirection = XMVector3TransformNormal(directionVector, inverseWorldMatrix);

	// Normalize the ray direction
	XMStoreFloat3(&direction, rayDirection);

	float rayDirectionLength = sqrt((direction.x * direction.x) + (direction.y * direction.y) + (direction.z * direction.z));
	direction.x = direction.x / rayDirectionLength;
	direction.y = direction.y / rayDirectionLength;
	direction.z = direction.z / rayDirectionLength;

	XMFLOAT3 rayOriginFloat;	
	XMStoreFloat3(&rayOriginFloat, rayOrigin);

	// Now perform the ray-sphere intersection test.
	intersect = RaySphereIntersect(rayOriginFloat, direction, 10000.0f);

	if (intersect == true)
	{
		// If it does intersect then set the intersection to "yes" in the text string that is displayed to the screen.
		// result = m_Text->SetIntersection(true, pGraphicsClass->m_D3D->GetDeviceContext());
	}
	else
	{
		// If not then set the intersection to "No".
		// result = m_Text->SetIntersection(false, pGraphicsClass->m_D3D->GetDeviceContext());
	}

	return intersect;
}

bool CollisionUtils::RaySphereIntersect(XMFLOAT3 rayOrigin, XMFLOAT3 rayDirection, float radius)
{
	float a, b, c, discriminant;


	// Calculate the a, b, and c coefficients.
	a = (rayDirection.x * rayDirection.x) + (rayDirection.y * rayDirection.y) + (rayDirection.z * rayDirection.z);
	b = ((rayDirection.x * rayOrigin.x) + (rayDirection.y * rayOrigin.y) + (rayDirection.z * rayOrigin.z)) * 2.0f;
	c = ((rayOrigin.x * rayOrigin.x) + (rayOrigin.y * rayOrigin.y) + (rayOrigin.z * rayOrigin.z)) - (radius * radius);

	// Find the discriminant.
	discriminant = (b * b) - (4 * a * c);

	// if discriminant is negative the picking ray missed the sphere, otherwise it intersected the sphere.
	if (discriminant < 0.0f)
	{
		return false;
	}

	return true;
}