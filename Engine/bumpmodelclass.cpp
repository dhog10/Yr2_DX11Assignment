////////////////////////////////////////////////////////////////////////////////
// Filename: bumpmodelclass.cpp
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <vector>
#include "bumpmodelclass.h"

BumpModelClass::BumpModelClass()
{
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_model = 0;
	m_ColorTexture = 0;
	m_NormalMapTexture = 0;
}


BumpModelClass::BumpModelClass(const BumpModelClass& other)
{
}


BumpModelClass::~BumpModelClass()
{
}


bool BumpModelClass::Initialize(ID3D11Device* device, char* modelFilename, WCHAR* textureFilename1, WCHAR* textureFilename2)
{
	bool result;

	int modelLen = strlen(modelFilename);
	modelLen -= 3;
	
	std::string model = modelFilename;

	if (model.substr(model.size() - 4, 4) == ".obj") {
		// Load in the model data,
		result = LoadModelOBJ(modelFilename);
		if (!result)
		{
			return false;
		}
	}
	else {
		// Load in the model data,
		result = LoadModel(modelFilename);
		if (!result)
		{
			return false;
		}
	}

	// Calculate the tangent and binormal vectors for the model.
	CalculateModelVectors();

	// Initialize the vertex and index buffers.
	result = InitializeBuffers(device);
	if(!result)
	{
		return false;
	}

	// Load the textures for this model.
	result = LoadTextures(device, textureFilename1, textureFilename2);
	if(!result)
	{
		return false;
	}

	return true;
}


void BumpModelClass::Shutdown()
{
	// Release the model textures.
	ReleaseTextures();

	// Shutdown the vertex and index buffers.
	ShutdownBuffers();

	// Release the model data.
	ReleaseModel();

	return;
}


void BumpModelClass::Render(ID3D11DeviceContext* deviceContext)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext);

	return;
}


int BumpModelClass::GetIndexCount()
{
	return m_indexCount;
}


ID3D11ShaderResourceView* BumpModelClass::GetColorTexture()
{
	return m_ColorTexture->GetTexture();
}


ID3D11ShaderResourceView* BumpModelClass::GetNormalMapTexture()
{
	return m_NormalMapTexture->GetTexture();
}


bool BumpModelClass::InitializeBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;
	int i;


	// Create the vertex array.
	vertices = new VertexType[m_vertexCount];
	if(!vertices)
	{
		return false;
	}

	// Create the index array.
	indices = new unsigned long[m_indexCount];
	if(!indices)
	{
		return false;
	}

	// Load the vertex array and index array with data.
	for(i=0; i<m_vertexCount; i++)
	{
		vertices[i].position = XMFLOAT3(m_model[i].x, m_model[i].y, m_model[i].z);
		vertices[i].texture = XMFLOAT2(m_model[i].tu, m_model[i].tv);
		vertices[i].normal = XMFLOAT3(m_model[i].nx, m_model[i].ny, m_model[i].nz);
		vertices[i].tangent = XMFLOAT3(m_model[i].tx, m_model[i].ty, m_model[i].tz);
		vertices[i].binormal = XMFLOAT3(m_model[i].bx, m_model[i].by, m_model[i].bz);

		indices[i] = i;
	}

	// Set up the description of the static vertex buffer.
    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = 0;
    vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the vertex data.
    vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
    result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Set up the description of the static index buffer.
    indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
    indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
    indexBufferDesc.CPUAccessFlags = 0;
    indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
    indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if(FAILED(result))
	{
		return false;
	}

	// Release the arrays now that the vertex and index buffers have been created and loaded.
	delete [] vertices;
	vertices = 0;

	delete [] indices;
	indices = 0;

	return true;
}


void BumpModelClass::ShutdownBuffers()
{
	// Release the index buffer.
	if(m_indexBuffer)
	{
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	// Release the vertex buffer.
	if(m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}


void BumpModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;


	// Set vertex buffer stride and offset.
	stride = sizeof(VertexType); 
	offset = 0;
    
	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

    // Set the index buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

    // Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}


bool BumpModelClass::LoadTextures(ID3D11Device* device, WCHAR* filename1, WCHAR* filename2)
{
	bool result;


	// Create the color texture object.
	m_ColorTexture = new TextureClass;
	if(!m_ColorTexture)
	{
		return false;
	}

	// Initialize the color texture object.
	result = m_ColorTexture->Initialize(device, filename1);
	if(!result)
	{
		return false;
	}

	// Create the normal map texture object.
	m_NormalMapTexture = new TextureClass;
	if(!m_NormalMapTexture)
	{
		return false;
	}

	// Initialize the normal map texture object.
	result = m_NormalMapTexture->Initialize(device, filename2);
	if(!result)
	{
		return false;
	}

	return true;
}


void BumpModelClass::ReleaseTextures()
{
	// Release the texture objects.
	if(m_ColorTexture)
	{
		m_ColorTexture->Shutdown();
		delete m_ColorTexture;
		m_ColorTexture = 0;
	}

	if(m_NormalMapTexture)
	{
		m_NormalMapTexture->Shutdown();
		delete m_NormalMapTexture;
		m_NormalMapTexture = 0;
	}

	return;
}

// This is a utility method used in the OBJ parser method

void SplitString(std::string* in, std::vector<std::string>* out, char token, int startFind) {
	int curFind = 0;
	int lastIndexLen = 0;

	out->clear();

	for (int i = 0; i < in->length(); i++) {
		char cur = in->at(i);

		if (cur == token || i == in->length() - 1) {
			curFind++;

			if (curFind > startFind && lastIndexLen >= 0) {
				int len = lastIndexLen;
				if (i == in->length() - 1) {
					len++;
				}

				std::string sub = in->substr(i - lastIndexLen, len);
				if (sub != "") {
					out->push_back(sub);
				}
			}

			lastIndexLen = 0;
		}
		else {
			lastIndexLen++;
		}
	}
}

// This is a utility method used in the OBJ parser method
// This method loads the information to the model array using provided information

void BumpModelClass::LoadFaceToModel(int i, XMFLOAT3 vert, XMFLOAT2 uv, XMFLOAT3 normal) {
	m_model[i].x = vert.x;
	m_model[i].y = vert.y;
	m_model[i].z = vert.z;

	m_model[i].tu = uv.x;
	m_model[i].tv = uv.y;

	m_model[i].nx = normal.x;
	m_model[i].ny = normal.y;
	m_model[i].nz = normal.z;
}

// Function to parse obj files
// Can parse an OBj file without the need of conversion to the text format that we originally used
// Can only parse OBJ files saved in triangle list order

bool BumpModelClass::LoadModelOBJ(char* filename)
{
	ifstream fin;
	char input;
	int i;
	string line;
	std::vector<XMFLOAT3> verts;
	std::vector<XMFLOAT2> uvs;
	std::vector<XMFLOAT3> normals;
	std::vector<TriFace> faces;

	std::vector<std::string> stemp;

	// Open the model file.  If it could not open the file then exit.
	fin.open(filename);
	if (fin.fail())
	{
		return false;
	}

	// Read up to end of file comments
	while (getline(fin, line)) {
		if (line.length() == 0) { continue; }
		if (line.at(0) == '#') { continue; }

		SplitString(&line, &stemp, ' ', 0);

		if (stemp.size() == 0) { continue; }

		if (stemp[0] == "v") {
			// Read vertex

			double x = atof(stemp[1].c_str());
			double y = atof(stemp[2].c_str());
			double z = atof(stemp[3].c_str());

			XMFLOAT3 vert = XMFLOAT3(x, y, z);
			verts.push_back(vert);
		}
		else if (stemp[0] == "vt") {
			// Read uv
			double x = atof(stemp[1].c_str());
			double y = atof(stemp[2].c_str());

			XMFLOAT2 uv = XMFLOAT2(x,1 - y);
			uvs.push_back(uv);
		}
		else if (stemp[0] == "vn") {
			// Read normal

			double x = atof(stemp[1].c_str());
			double y = atof(stemp[2].c_str());
			double z = atof(stemp[3].c_str());

			XMFLOAT3 normal = XMFLOAT3(x, y, z);
			normals.push_back(normal);
		}
		else if (stemp[0] == "f") {
			// Read face
			// f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3 ...

			TriFace face;
			FaceVertex v1, v2, v3;

			std::string face1 = stemp[1];
			std::string face2 = stemp[2];
			std::string face3 = stemp[3];

			int indexOffset = -1;

			SplitString(&face1, &stemp, '/', 0);
			v1.v = std::stoi(stemp[0]) + indexOffset;
			v1.vt = std::stoi(stemp[1]) + indexOffset;
			v1.vn = std::stoi(stemp[2]) + indexOffset;

			SplitString(&face2, &stemp, '/', 0);
			v2.v = std::stoi(stemp[0]) + indexOffset;
			v2.vt = std::stoi(stemp[1]) + indexOffset;
			v2.vn = std::stoi(stemp[2]) + indexOffset;

			SplitString(&face3, &stemp, '/', 0);
			v3.v = std::stoi(stemp[0]) + indexOffset;
			v3.vt = std::stoi(stemp[1]) + indexOffset;
			v3.vn = std::stoi(stemp[2]) + indexOffset;

			face.v1 = v1;
			face.v2 = v2;
			face.v3 = v3;

			faces.insert(faces.begin(), face);
		}
	}

	m_vertexCount = faces.size() * 3;
	m_indexCount = m_vertexCount;
	m_model = new ModelType[m_vertexCount];

	int placeIndex = 0;

	// Load face data into model
	for (int i = faces.size() - 1; i >= 0 ; i--) {
		TriFace face = faces[i];

		LoadFaceToModel(placeIndex++, verts[face.v1.v], uvs[face.v1.vt], normals[face.v1.vn]);
		LoadFaceToModel(placeIndex++, verts[face.v2.v], uvs[face.v2.vt], normals[face.v2.vn]);
		LoadFaceToModel(placeIndex++, verts[face.v3.v], uvs[face.v3.vt], normals[face.v3.vn]);
	}

	return true;
}

bool BumpModelClass::LoadModel(char* filename)
{
	ifstream fin;
	char input;
	int i;


	// Open the model file.  If it could not open the file then exit.
	fin.open(filename);
	if(fin.fail())
	{
		return false;
	}

	// Read up to the value of vertex count.
	fin.get(input);
	while(input != ':')
	{
		fin.get(input);
	}

	// Read in the vertex count.
	fin >> m_vertexCount;

	// Set the number of indices to be the same as the vertex count.
	m_indexCount = m_vertexCount;

	// Create the model using the vertex count that was read in.
	m_model = new ModelType[m_vertexCount];
	if(!m_model)
	{
		return false;
	}

	// Read up to the beginning of the data.
	fin.get(input);
	while(input != ':')
	{
		fin.get(input);
	}
	fin.get(input);
	fin.get(input);

	// Read in the vertex data.
	for(i=0; i<m_vertexCount; i++)
	{
		fin >> m_model[i].x >> m_model[i].y >> m_model[i].z;
		fin >> m_model[i].tu >> m_model[i].tv;
		fin >> m_model[i].nx >> m_model[i].ny >> m_model[i].nz;
	}

	// Close the model file.
	fin.close();

	return true;
}


void BumpModelClass::ReleaseModel()
{
	if(m_model)
	{
		delete [] m_model;
		m_model = 0;
	}

	return;
}


void BumpModelClass::CalculateModelVectors()
{
	int faceCount, i, index;
	TempVertexType vertex1, vertex2, vertex3;
	VectorType tangent, binormal;


	// Calculate the number of faces in the model.
	faceCount = m_vertexCount / 3;

	// Initialize the index to the model data.
	index = 0;

	// Go through all the faces and calculate the the tangent, binormal, and normal vectors.
	for(i=0; i<faceCount; i++)
	{
		// Get the three vertices for this face from the model.
		vertex1.x = m_model[index].x;
		vertex1.y = m_model[index].y;
		vertex1.z = m_model[index].z;
		vertex1.tu = m_model[index].tu;
		vertex1.tv = m_model[index].tv;
		vertex1.nx = m_model[index].nx;
		vertex1.ny = m_model[index].ny;
		vertex1.nz = m_model[index].nz;
		index++;

		vertex2.x = m_model[index].x;
		vertex2.y = m_model[index].y;
		vertex2.z = m_model[index].z;
		vertex2.tu = m_model[index].tu;
		vertex2.tv = m_model[index].tv;
		vertex2.nx = m_model[index].nx;
		vertex2.ny = m_model[index].ny;
		vertex2.nz = m_model[index].nz;
		index++;

		vertex3.x = m_model[index].x;
		vertex3.y = m_model[index].y;
		vertex3.z = m_model[index].z;
		vertex3.tu = m_model[index].tu;
		vertex3.tv = m_model[index].tv;
		vertex3.nx = m_model[index].nx;
		vertex3.ny = m_model[index].ny;
		vertex3.nz = m_model[index].nz;
		index++;

		// Calculate the tangent and binormal of that face.
		CalculateTangentBinormal(vertex1, vertex2, vertex3, tangent, binormal);

		// Store the normal, tangent, and binormal for this face back in the model structure.
		m_model[index-1].tx = tangent.x;
		m_model[index-1].ty = tangent.y;
		m_model[index-1].tz = tangent.z;
		m_model[index-1].bx = binormal.x;
		m_model[index-1].by = binormal.y;
		m_model[index-1].bz = binormal.z;

		m_model[index-2].tx = tangent.x;
		m_model[index-2].ty = tangent.y;
		m_model[index-2].tz = tangent.z;
		m_model[index-2].bx = binormal.x;
		m_model[index-2].by = binormal.y;
		m_model[index-2].bz = binormal.z;

		m_model[index-3].tx = tangent.x;
		m_model[index-3].ty = tangent.y;
		m_model[index-3].tz = tangent.z;
		m_model[index-3].bx = binormal.x;
		m_model[index-3].by = binormal.y;
		m_model[index-3].bz = binormal.z;
	}

	return;
}


void BumpModelClass::CalculateTangentBinormal(TempVertexType vertex1, TempVertexType vertex2, TempVertexType vertex3,
										  VectorType& tangent, VectorType& binormal)
{
	float vector1[3], vector2[3];
	float tuVector[2], tvVector[2];
	float den;
	float length;


	// Calculate the two vectors for this face.
	vector1[0] = vertex2.x - vertex1.x;
	vector1[1] = vertex2.y - vertex1.y;
	vector1[2] = vertex2.z - vertex1.z;

	vector2[0] = vertex3.x - vertex1.x;
	vector2[1] = vertex3.y - vertex1.y;
	vector2[2] = vertex3.z - vertex1.z;

	// Calculate the tu and tv texture space vectors.
	tuVector[0] = vertex2.tu - vertex1.tu;
	tvVector[0] = vertex2.tv - vertex1.tv;

	tuVector[1] = vertex3.tu - vertex1.tu;
	tvVector[1] = vertex3.tv - vertex1.tv;

	// Calculate the denominator of the tangent/binormal equation.
	den = 1.0f / (tuVector[0] * tvVector[1] - tuVector[1] * tvVector[0]);

	// Calculate the cross products and multiply by the coefficient to get the tangent and binormal.
	tangent.x = (tvVector[1] * vector1[0] - tvVector[0] * vector2[0]) * den;
	tangent.y = (tvVector[1] * vector1[1] - tvVector[0] * vector2[1]) * den;
	tangent.z = (tvVector[1] * vector1[2] - tvVector[0] * vector2[2]) * den;

	binormal.x = (tuVector[0] * vector2[0] - tuVector[1] * vector1[0]) * den;
	binormal.y = (tuVector[0] * vector2[1] - tuVector[1] * vector1[1]) * den;
	binormal.z = (tuVector[0] * vector2[2] - tuVector[1] * vector1[2]) * den;

	// Calculate the length of this normal.
	length = sqrt((tangent.x * tangent.x) + (tangent.y * tangent.y) + (tangent.z * tangent.z));
			
	// Normalize the normal and then store it
	tangent.x = tangent.x / length;
	tangent.y = tangent.y / length;
	tangent.z = tangent.z / length;

	// Calculate the length of this normal.
	length = sqrt((binormal.x * binormal.x) + (binormal.y * binormal.y) + (binormal.z * binormal.z));
			
	// Normalize the normal and then store it
	binormal.x = binormal.x / length;
	binormal.y = binormal.y / length;
	binormal.z = binormal.z / length;

	return;
}