//=============================================================================
//                              Cylinder3D
//
// Written by Adi Bar-Lev, 2013
// EGP 300-101, Graphics Programming II  - skeleton project
//=============================================================================
#include "Cylinder3D.h"
#include "Vertex.h"
#include "../GfxStats.h"

#define _USE_MATH_DEFINES
#include <math.h>

//=============================================================================
Cylinder3D::Cylinder3D(float height, float radius, int numSegments)
	: mHeight(height), mRadius(radius), mNumSegments(numSegments)
{
    m_VertexBuffer = NULL;
    m_IndexBuffer = NULL;

    D3DXMatrixIdentity(&m_World);
}

//-----------------------------------------------------------------------------
Cylinder3D::~Cylinder3D(void)
{
    ReleaseCOM(m_VertexBuffer);
	ReleaseCOM(m_IndexBuffer);
}

//-----------------------------------------------------------------------------
void Cylinder3D::Create(IDirect3DDevice9* gd3dDevice)
{
	buildCylinderVertexBuffer( gd3dDevice );
	buildCylinderIndexBuffer( gd3dDevice );
}

//-----------------------------------------------------------------------------
void Cylinder3D::buildCylinderVertexBuffer(IDirect3DDevice9* gd3dDevice)
{
	mNumVertices = (mNumSegments + 1 ) *2; //2 vertices for each section plus a vertex in the center on the top and bottom.

	// Obtain a pointer to a new vertex buffer.
	HR(gd3dDevice->CreateVertexBuffer(mNumVertices * sizeof(VertexPos), D3DUSAGE_WRITEONLY,
		0, D3DPOOL_MANAGED, &m_VertexBuffer, 0));

	// Now lock it to obtain a pointer to its internal data, and write the
	// cylinder's vertex data.
	VertexPos* v = 0;
	HR(m_VertexBuffer->Lock(0, 0, (void**)&v, 0));


	//put top and bottom center vertex at the end
	v[mNumVertices - 2] = VertexPos(0, mHeight*-0.5f, 0);//bottom center vertex
	v[mNumVertices - 1] = VertexPos(0, mHeight*0.5f, 0);//top center vertex

	//generate section vertices
	float degreesPerSegment = 360.0f / mNumSegments;
	float radsPerSegment = (float)(degreesPerSegment * M_PI / 180.0f);
	float theta, x, z;
	//generate bottom vertices
	for (int i = 0; i < mNumSegments; i++)
	{
		theta = i*radsPerSegment;
		x = cos(theta) * mRadius;
		z = sin(theta) * mRadius;
		v[i] = VertexPos(x, mHeight*-0.5f, z);
	}
	//generate top vertices
	int topVertexStart = mNumSegments;
	for (int i = 0; i < mNumSegments; i++)
	{
		theta = i*radsPerSegment;
		x = cos(theta) * mRadius;
		z = sin(theta) * mRadius;
		v[i + topVertexStart] = VertexPos(x, mHeight*0.5f, z);
	}
	

	HR(m_VertexBuffer->Unlock());
}
void Cylinder3D::buildCylinderIndexBuffer(IDirect3DDevice9* gd3dDevice)
{
	mNumTriangles = mNumSegments * 4;//4 triangles per section

	// Obtain a pointer to a new index buffer.
	//number of triangles times 3 to get number of indices in total
	HR(gd3dDevice->CreateIndexBuffer(mNumTriangles*3 * sizeof(WORD), D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_IndexBuffer, 0));

	// Now lock it to obtain a pointer to its internal data, and write the
	// cylinder's index data.

	WORD* k = 0;

	HR(m_IndexBuffer->Lock(0, 0, (void**)&k, 0));
	

	//*
	int triIndex;
	int vertIndex;
	int topVertexStart = mNumSegments;
	int topTriStart = topVertexStart * 3;
	//TODO: do last section manually (due to wrap around)
	//generate top/bottom indices
	for (int i = 0; i < mNumSegments-1; i++)
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
		vertIndex = mNumSegments - 1;
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
	for (int i = 0; i < mNumSegments - 1; i++)
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
		vertIndex = mNumSegments - 1;
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


	HR(m_IndexBuffer->Unlock());
}
//=============================================================================
