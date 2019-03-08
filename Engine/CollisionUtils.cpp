#include "CollisionUtils.h"
#include "d3dclass.h"



void CollisionUtils::PickRayVector(float mouseX, float mouseY, XMVECTOR & pickRayInWorldSpacePos, XMVECTOR & pickRayInWorldSpaceDir, int ScrWidth, int ScrHeight)
{
	XMVECTOR pickRayInViewSpaceDir = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR pickRayInViewSpacePos = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);

	float PRVecX, PRVecY, PRVecZ;

	//Transform 2D pick position on screen space to 3D ray in View space
	PRVecX = (((2.0f * mouseX) / ScrWidth) - 1) / camProjection(0, 0);
	PRVecY = -(((2.0f * mouseY) / ScrHeight) - 1) / camProjection(1, 1);
	PRVecZ = 1.0f;	//View space's Z direction ranges from 0 to 1, so we set 1 since the ray goes "into" the screen

	pickRayInViewSpaceDir = XMVectorSet(PRVecX, PRVecY, PRVecZ, 0.0f);

	//Uncomment this line if you want to use the center of the screen (client area)
	//to be the point that creates the picking ray (eg. first person shooter)
	//pickRayInViewSpaceDir = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);

	// Transform 3D Ray from View space to 3D ray in World space
	XMMATRIX pickRayToWorldSpaceMatrix;
	XMVECTOR matInvDeter;	//We don't use this, but the xna matrix inverse function requires the first parameter to not be null

	pickRayToWorldSpaceMatrix = XMMatrixInverse(&matInvDeter, camView);	//Inverse of View Space matrix is World space matrix

	pickRayInWorldSpacePos = XMVector3TransformCoord(pickRayInViewSpacePos, pickRayToWorldSpaceMatrix);
	pickRayInWorldSpaceDir = XMVector3TransformNormal(pickRayInViewSpaceDir, pickRayToWorldSpaceMatrix);
}
