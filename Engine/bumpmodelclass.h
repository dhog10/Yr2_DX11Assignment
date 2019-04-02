////////////////////////////////////////////////////////////////////////////////
// Filename: bumpmodelclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _BUMPMODELCLASS_H_
#define _BUMPMODELCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11_1.h>
#include <directXMath.h>
using namespace DirectX;

#include <fstream>
#include <vector>
using namespace std;


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "textureclass.h"

struct FaceVertex {
	int v;
	int vt;
	int vn;
};

struct TriFace {
	FaceVertex v1;
	FaceVertex v2;
	FaceVertex v3;
};

struct ModelType
{
	float x, y, z;
	float tu, tv;
	float nx, ny, nz;
	float tx, ty, tz;
	float bx, by, bz;
};

struct VertexData;

////////////////////////////////////////////////////////////////////////////////
// Class name: BumpModelClass
////////////////////////////////////////////////////////////////////////////////
class BumpModelClass
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
		XMFLOAT3 normal;
		XMFLOAT3 tangent;
		XMFLOAT3 binormal;
	};

	struct TempVertexType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

	struct VectorType
	{
		float x, y, z;
	};

public:
	BumpModelClass();
	BumpModelClass(const BumpModelClass&);
	~BumpModelClass();

	bool Initialize(ID3D11Device*, char*, WCHAR*, WCHAR*);
	bool InitializeFromVertexArray(ID3D11Device*, VertexData, WCHAR*);
	void Shutdown();
	void Render(ID3D11DeviceContext*);

	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	ModelType* m_model;

	int GetIndexCount();
	int GetVertexCount();
	void SetIndexCount(int);
	void SetVertexCount(int);
	void InitializeModel();

	ID3D11ShaderResourceView* GetColorTexture();
	ID3D11ShaderResourceView* GetNormalMapTexture();

	void CalculateModelVectors();
	bool InitializeBuffers(ID3D11Device*);
private:
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTextures(ID3D11Device*, WCHAR*, WCHAR*);
	void ReleaseTextures();

	bool LoadModel(char*);
	bool LoadModelOBJ(char*);
	bool LoadModelFromVertices(VertexData);
	void LoadFaceToModel(int, XMFLOAT3, XMFLOAT2, XMFLOAT3);
	void ReleaseModel();

	void CalculateTangentBinormal(TempVertexType, TempVertexType, TempVertexType, VectorType&, VectorType&);

private:
	int m_vertexCount, m_indexCount;
	TextureClass* m_ColorTexture;
	TextureClass* m_NormalMapTexture;
};

#endif