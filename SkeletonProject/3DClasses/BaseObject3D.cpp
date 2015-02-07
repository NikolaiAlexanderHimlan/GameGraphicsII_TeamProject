//=============================================================================
//                              BaseObject3D
//
// Written by Adi Bar-Lev, 2013
// EGP 300-101, Graphics Programming II  - skeleton project
//
// Base class that can handle 3D rendering via Vertex and Index buffer
//=============================================================================
#include "BaseObject3D.h"
#include "Vertex.h"
#include "../GfxStats.h"

#define _USE_MATH_DEFINES
#include <math.h>

//=============================================================================
BaseObject3D::BaseObject3D(void)
{
    m_VertexBuffer = NULL;
    m_IndexBuffer = NULL;

    D3DXMatrixIdentity(&m_World);
}

//-----------------------------------------------------------------------------
BaseObject3D::~BaseObject3D(void)
{
    ReleaseCOM(m_VertexBuffer);
	ReleaseCOM(m_IndexBuffer);
}

//-----------------------------------------------------------------------------
void BaseObject3D::setWorldPosition(const Vector3f& newPosition)
{
	m_World = *D3DXMatrixTranslation(&m_World, newPosition.x, newPosition.y, newPosition.z);
}

//-----------------------------------------------------------------------------
void BaseObject3D::Create( IDirect3DDevice9* gd3dDevice, PrimitiveType createPrimitive )
{
	switch (createPrimitive)
	{
	default://default to cube if no other
	case CUBE:
    buildDemoCubeVertexBuffer( gd3dDevice );
    buildDemoCubeIndexBuffer( gd3dDevice );
		break;
	case CONE:
		buildDemoConeVertexBuffer( gd3dDevice );
		buildDemoConeIndexBuffer( gd3dDevice );
		break;
	case CYLINDER:
		buildDemoCylinderVertexBuffer(gd3dDevice);
		buildDemoCylinderIndexBuffer(gd3dDevice);
		break;
	}
}

//-----------------------------------------------------------------------------
void BaseObject3D::Render( IDirect3DDevice9* gd3dDevice,
    D3DXMATRIX& view, D3DXMATRIX& projection )
{
    // Update the statistics singleton class
	GfxStats::GetInstance()->addVertices(getVertexCount());
	GfxStats::GetInstance()->addTriangles(getTriangleCount());

    // Set the buffers and format
    HR(gd3dDevice->SetStreamSource(0, m_VertexBuffer, 0, sizeof(VertexPos)));
	HR(gd3dDevice->SetIndices(m_IndexBuffer));
	HR(gd3dDevice->SetVertexDeclaration(VertexPos::Decl));

    // Set matrices and model relevant render date
	HR(gd3dDevice->SetTransform(D3DTS_WORLD, &m_World));
	HR(gd3dDevice->SetTransform(D3DTS_VIEW, &view));
	HR(gd3dDevice->SetTransform(D3DTS_PROJECTION, &projection));	
    
    // Send to render
    HR(gd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, getVertexCount(), 0, getTriangleCount()));
}

//-----------------------------------------------------------------------------
void BaseObject3D::buildDemoCubeVertexBuffer( IDirect3DDevice9* gd3dDevice )
{
	mNumVertices = 8;

	// Obtain a pointer to a new vertex buffer.
	HR(gd3dDevice->CreateVertexBuffer(8 * sizeof(VertexPos), D3DUSAGE_WRITEONLY,
		0, D3DPOOL_MANAGED, &m_VertexBuffer, 0));

	// Now lock it to obtain a pointer to its internal data, and write the
	// cube's vertex data.

	VertexPos* v = 0;
	HR(m_VertexBuffer->Lock(0, 0, (void**)&v, 0));

	v[0] = VertexPos(-1.0f, -1.0f, -1.0f);
	v[1] = VertexPos(-1.0f,  1.0f, -1.0f);
	v[2] = VertexPos( 1.0f,  1.0f, -1.0f);
	v[3] = VertexPos( 1.0f, -1.0f, -1.0f);
	v[4] = VertexPos(-1.0f, -1.0f,  1.0f);
	v[5] = VertexPos(-1.0f,  1.0f,  1.0f);
	v[6] = VertexPos( 1.0f,  1.0f,  1.0f);
	v[7] = VertexPos( 1.0f, -1.0f,  1.0f);

	HR(m_VertexBuffer->Unlock());
}

//-----------------------------------------------------------------------------
void BaseObject3D::buildDemoCubeIndexBuffer( IDirect3DDevice9* gd3dDevice )
{
	mNumTriangles = 36 / 3;

	// Obtain a pointer to a new index buffer.
	HR(gd3dDevice->CreateIndexBuffer(36 * sizeof(WORD), D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_IndexBuffer, 0));

	// Now lock it to obtain a pointer to its internal data, and write the
	// cube's index data.

	WORD* k = 0;

	HR(m_IndexBuffer->Lock(0, 0, (void**)&k, 0));

	// Front face.
	k[0] = 0; k[1] = 1; k[2] = 2;
	k[3] = 0; k[4] = 2; k[5] = 3;

	// Back face.
	k[6] = 4; k[7]  = 6; k[8]  = 5;
	k[9] = 4; k[10] = 7; k[11] = 6;

	// Left face.
	k[12] = 4; k[13] = 5; k[14] = 1;
	k[15] = 4; k[16] = 1; k[17] = 0;

	// Right face.
	k[18] = 3; k[19] = 2; k[20] = 6;
	k[21] = 3; k[22] = 6; k[23] = 7;

	// Top face.
	k[24] = 1; k[25] = 5; k[26] = 6;
	k[27] = 1; k[28] = 6; k[29] = 2;

	// Bottom face.
	k[30] = 4; k[31] = 0; k[32] = 3;
	k[33] = 4; k[34] = 3; k[35] = 7;

	HR(m_IndexBuffer->Unlock());
}

//-----------------------------------------------------------------------------
void BaseObject3D::buildDemoConeVertexBuffer(IDirect3DDevice9* gd3dDevice)
{
	mNumVertices = mPrimitive_NumSections + 2; //1 vertex for each section plus a vertex in the center on the top and bottom.

	// Obtain a pointer to a new vertex buffer.
	HR(gd3dDevice->CreateVertexBuffer(mNumVertices * sizeof(VertexPos), D3DUSAGE_WRITEONLY,
		0, D3DPOOL_MANAGED, &m_VertexBuffer, 0));

	// Now lock it to obtain a pointer to its internal data, and write the
	// cylinder's vertex data.
	VertexPos* v = 0;
	HR(m_VertexBuffer->Lock(0, 0, (void**)&v, 0));

	//put top and bottom center vertex at the end
	v[mNumVertices - 2] = VertexPos(0, mPrimitive_Height*-0.5f, 0);//bottom center vertex
	v[mNumVertices - 1] = VertexPos(0, mPrimitive_Height*0.5f, 0);//top center vertex

	float degreesPerSegment = 360.0f / mPrimitive_NumSections;
	float radsPerSegment = (float)(degreesPerSegment * M_PI / 180.0f);
	float theta, x, z;
	for (int i = 0; i < mPrimitive_NumSections; i++)
	{
		theta = i*radsPerSegment;
		x = cos(theta);
		z = sin(theta);
		v[i] = VertexPos(x, mPrimitive_Height*-0.5f, z);
	}


	HR(m_VertexBuffer->Unlock());
}
void BaseObject3D::buildDemoConeIndexBuffer(IDirect3DDevice9* gd3dDevice)
{
	mNumTriangles = mPrimitive_NumSections * 2;//2 triangles per section

	// Obtain a pointer to a new index buffer.
	//number of triangles times 3 to get number of indices in total
	HR(gd3dDevice->CreateIndexBuffer(mNumTriangles * 3 * sizeof(WORD), D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_IndexBuffer, 0));

	// Now lock it to obtain a pointer to its internal data, and write the
	// cylinder's index data.

	WORD* k = 0;

	HR(m_IndexBuffer->Lock(0, 0, (void**)&k, 0));


	/*connecting every vertex to 0
	int vertIndex;
	for (int i = 0; i < mNumVertices; i++)
	{
		vertIndex = i * 3;//give each vertex a triangle
		k[vertIndex] = i;
		k[vertIndex + 1] = 0;
		k[vertIndex + 2] = 0;
	}
	//*/

	/*Hard-coded indices (4 sections)
	// Section 1 face.
	k[0] = 0; k[1] = 1; k[2] = 4;
	// Section 1 bottom.
	k[3] = 0; k[4] = 1; k[5] = 5;

	// Section 2 face.
	k[6] = 1; k[7] = 2; k[8] = 4;
	// Section 2 bottom.
	k[9] = 1; k[10] = 2; k[11] = 5;

	// Section 3 face.
	k[12] = 2; k[13] = 3; k[14] = 4;
	// Section 3 bottom.
	k[15] = 2; k[16] = 3; k[17] = 5;

	// Section 4 face.
	k[18] = 3; k[19] = 0; k[20] = 4;
	// Section 4 bottom.
	k[21] = 3; k[22] = 0; k[23] = 5;
	//*/

	//*
	int triIndex;
	//do last section manually (due to wrap around)
	for (int i = 0; i < mPrimitive_NumSections-1; i++)
	{
		triIndex = i * 3 * 2;//3 indices per triangle, doing 2 triangles

		//bottom triangles
		k[triIndex + 0] = i;//vertex i
		k[triIndex + 1] = i + 1;//connect to next vertex section
		k[triIndex + 2] = mNumVertices - 2;//connect to top

		//side triangles
		k[triIndex + 4] = i;//vertex i
		k[triIndex + 3] = i + 1;//connect to next vertex section
		k[triIndex + 5] = mNumVertices - 1;//connect to bottom
	}

	//last section wrap around
	int lastIndex = mPrimitive_NumSections - 1;
	triIndex = lastIndex * 3 * 2;

	//bottom triangles
	k[triIndex + 0] = lastIndex;//vertex section vertex
	k[triIndex + 1] = 0;//wrap around back to first index
	k[triIndex + 2] = mNumVertices - 2;//connect to top

	//side triangles
	k[triIndex + 4] = lastIndex;//vertex i
	k[triIndex + 3] = 0;//wrap around back to first index
	k[triIndex + 5] = mNumVertices - 1;//connect to bottom
	//*/


	HR(m_IndexBuffer->Unlock());
}

//-----------------------------------------------------------------------------
void BaseObject3D::buildDemoCylinderVertexBuffer(IDirect3DDevice9* gd3dDevice)
{
	mNumVertices = (mPrimitive_NumSections + 1 ) *2; //2 vertices for each section plus a vertex in the center on the top and bottom.

	// Obtain a pointer to a new vertex buffer.
	HR(gd3dDevice->CreateVertexBuffer(mNumVertices * sizeof(VertexPos), D3DUSAGE_WRITEONLY,
		0, D3DPOOL_MANAGED, &m_VertexBuffer, 0));

	// Now lock it to obtain a pointer to its internal data, and write the
	// cylinder's vertex data.
	VertexPos* v = 0;
	HR(m_VertexBuffer->Lock(0, 0, (void**)&v, 0));


	//put top and bottom center vertex at the end
	v[mNumVertices - 2] = VertexPos(0, mPrimitive_Height*-0.5f, 0);//bottom center vertex
	v[mNumVertices - 1] = VertexPos(0, mPrimitive_Height*0.5f, 0);//top center vertex

	//generate section vertices
	float degreesPerSegment = 360.0f / mPrimitive_NumSections;
	float radsPerSegment = (float)(degreesPerSegment * M_PI / 180.0f);
	float theta, x, z;
	//generate bottom vertices
	for (int i = 0; i < mPrimitive_NumSections; i++)
	{
		theta = i*radsPerSegment;
		x = cos(theta);
		z = sin(theta);
		v[i] = VertexPos(x, mPrimitive_Height*-0.5f, z);
	}
	//generate top vertices
	int topVertexStart = mPrimitive_NumSections;
	for (int i = 0; i < mPrimitive_NumSections; i++)
	{
		theta = i*radsPerSegment;
		x = cos(theta);
		z = sin(theta);
		v[i + topVertexStart] = VertexPos(x, mPrimitive_Height*0.5f, z);
	}
	

	HR(m_VertexBuffer->Unlock());
}
void BaseObject3D::buildDemoCylinderIndexBuffer(IDirect3DDevice9* gd3dDevice)
{
	mNumTriangles = mPrimitive_NumSections * 4;//4 triangles per section

	// Obtain a pointer to a new index buffer.
	//number of triangles times 3 to get number of indices in total
	HR(gd3dDevice->CreateIndexBuffer(mNumTriangles*3 * sizeof(WORD), D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_IndexBuffer, 0));

	// Now lock it to obtain a pointer to its internal data, and write the
	// cylinder's index data.

	WORD* k = 0;

	HR(m_IndexBuffer->Lock(0, 0, (void**)&k, 0));
	

	//for (int i = 0; i < mNumTriangles*3; i++) k[i] = 0;//initialize all values with 0
	/*
	for (int i = 0; i < mNumVertices; i++)//connect every vertex to the top and bottom
	{
		int triIndex = i * 3;// *2;//3 indices per triangle, doing 2 triangles
		k[triIndex] = i;
		k[triIndex + 1] = mNumVertices - 2;
		k[triIndex + 2] = mNumVertices - 1;
	}
	*/

	//*
	int triIndex;
	int vertIndex;
	int topVertexStart = mPrimitive_NumSections;
	int topTriStart = topVertexStart * 3;
	//TODO: do last section manually (due to wrap around)
	//generate top/bottom indices
	for (int i = 0; i < mPrimitive_NumSections-1; i++)
	{
		triIndex = i * 3;//3 indices per triangle
		vertIndex = i;

		//Top
		k[triIndex + 0] = mNumVertices - 2;//center of top
		k[triIndex + 1] = vertIndex;//current section index
		k[triIndex + 2] = vertIndex +1;//next section index

		//Bottom
		k[triIndex + 0 + topTriStart] = mNumVertices - 1;//center of bottom
		k[triIndex + 2 + topTriStart] = vertIndex +topVertexStart;
		k[triIndex + 1 + topTriStart] = vertIndex +1 +topVertexStart;
	}
	//*wrap top/bottom indices
	{
		vertIndex = mPrimitive_NumSections - 1;
		triIndex = vertIndex * 3;// *2;//3 indices per triangle, doing 2 triangles

		//Top
		k[triIndex + 0] = mNumVertices - 2;//center of top
		k[triIndex + 1] = vertIndex;//current section index
		k[triIndex + 2] = 0;//first section index

		//Bottom
		k[triIndex + 0 + topTriStart] = mNumVertices - 1;//center of bottom
		k[triIndex + 2 + topTriStart] = vertIndex + topVertexStart;
		k[triIndex + 1 + topTriStart] = 0 + topVertexStart;//first section index
	}//*/
	//generate sides indices
	int sideTriStart = topTriStart * 2;//skip the indices from the top/bottom
	for (int i = 0; i < mPrimitive_NumSections - 1; i++)
	{
		triIndex = i * 3 + sideTriStart;//3 indices per triangle, doing 2 triangles
		vertIndex = i;

		//Top
		k[triIndex + 0] = vertIndex + topVertexStart;//opposite index
		k[triIndex + 2] = vertIndex;//current section index
		k[triIndex + 1] = vertIndex + 1;//next section index

		//Bottom
		k[triIndex + 0 + topTriStart] = vertIndex + 1;//opposite index
		k[triIndex + 1 + topTriStart] = vertIndex + topVertexStart;//current section index
		k[triIndex + 2 + topTriStart] = vertIndex + 1 + topVertexStart;//next section index
	}
	//*wrap side indices
	{
		vertIndex = mPrimitive_NumSections - 1;
		triIndex = vertIndex * 3 + sideTriStart;//3 indices per triangle, doing 2 triangles

		//Top
		k[triIndex + 0] = vertIndex + topVertexStart;//opposite index
		k[triIndex + 2] = vertIndex;//current section index
		k[triIndex + 1] = 0;//first section index

		//Bottom
		k[triIndex + 0 + topTriStart] = 0;//opposite index
		k[triIndex + 1 + topTriStart] = vertIndex + topVertexStart;//current section index
		k[triIndex + 2 + topTriStart] = 0 + topVertexStart;//first section index
	}//*/
	//*/


	HR(m_IndexBuffer->Unlock());
}

//=============================================================================
