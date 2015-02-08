//=============================================================================
//                              Primitive3D
//
// Written by Adi Bar-Lev, 2013
// EGP 300-101, Graphics Programming II  - skeleton project
//
// Base class that can handle 3D rendering via Vertex and Index buffer
//=============================================================================
#include "Primitive3D.h"
#include "Vertex.h"
#include "../GfxStats.h"

#define _USE_MATH_DEFINES
#include <math.h>

//=============================================================================
Primitive3D::Primitive3D(void)
{
    m_VertexBuffer = NULL;
    m_IndexBuffer = NULL;

    D3DXMatrixIdentity(&m_World);
}

//-----------------------------------------------------------------------------
Primitive3D::~Primitive3D(void)
{
    ReleaseCOM(m_VertexBuffer);
	ReleaseCOM(m_IndexBuffer);
}

//-----------------------------------------------------------------------------
void Primitive3D::buildConeVertexBuffer(IDirect3DDevice9* gd3dDevice, float height, float radius, int numSegments)
{
	mNumVertices = numSegments + 2; //1 vertex for each section plus a vertex in the center on the top and bottom.

	// Obtain a pointer to a new vertex buffer.
	HR(gd3dDevice->CreateVertexBuffer(mNumVertices * sizeof(VertexPos), D3DUSAGE_WRITEONLY,
		0, D3DPOOL_MANAGED, &m_VertexBuffer, 0));

	// Now lock it to obtain a pointer to its internal data, and write the
	// cylinder's vertex data.
	VertexPos* v = 0;
	HR(m_VertexBuffer->Lock(0, 0, (void**)&v, 0));

	//put top and bottom center vertex at the end
	v[mNumVertices - 2] = VertexPos(0, height*-0.5f, 0);//bottom center vertex
	v[mNumVertices - 1] = VertexPos(0, height*0.5f, 0);//top center vertex

	float degreesPerSegment = 360.0f / numSegments;
	float radsPerSegment = (float)(degreesPerSegment * M_PI / 180.0f);
	float theta, x, z;
	for (int i = 0; i < numSegments; i++)
	{
		theta = i*radsPerSegment;
		x = cos(theta) * radius;
		z = sin(theta) * radius;
		v[i] = VertexPos(x, height*-0.5f, z);
	}


	HR(m_VertexBuffer->Unlock());
}
void Primitive3D::buildConeIndexBuffer(IDirect3DDevice9* gd3dDevice, float height, float radius, int numSegments)
{
	mNumTriangles = numSegments * 2;//2 triangles per section

	// Obtain a pointer to a new index buffer.
	//number of triangles times 3 to get number of indices in total
	HR(gd3dDevice->CreateIndexBuffer(mNumTriangles * 3 * sizeof(WORD), D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_IndexBuffer, 0));

	// Now lock it to obtain a pointer to its internal data, and write the
	// cylinder's index data.

	WORD* k = 0;

	HR(m_IndexBuffer->Lock(0, 0, (void**)&k, 0));


	int triIndex;
	//do last section manually (due to wrap around)
	for (int i = 0; i < numSegments-1; i++)
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
	int lastIndex = numSegments - 1;
	triIndex = lastIndex * 3 * 2;

	//bottom triangles
	k[triIndex + 0] = lastIndex;//vertex section vertex
	k[triIndex + 1] = 0;//wrap around back to first index
	k[triIndex + 2] = mNumVertices - 2;//connect to top

	//side triangles
	k[triIndex + 4] = lastIndex;//vertex i
	k[triIndex + 3] = 0;//wrap around back to first index
	k[triIndex + 5] = mNumVertices - 1;//connect to bottom


	HR(m_IndexBuffer->Unlock());
}

//-----------------------------------------------------------------------------
void Primitive3D::buildCylinderVertexBuffer(IDirect3DDevice9* gd3dDevice, float height, float radius, int numSegments)
{
	mNumVertices = (numSegments + 1 ) *2; //2 vertices for each section plus a vertex in the center on the top and bottom.

	// Obtain a pointer to a new vertex buffer.
	HR(gd3dDevice->CreateVertexBuffer(mNumVertices * sizeof(VertexPos), D3DUSAGE_WRITEONLY,
		0, D3DPOOL_MANAGED, &m_VertexBuffer, 0));

	// Now lock it to obtain a pointer to its internal data, and write the
	// cylinder's vertex data.
	VertexPos* v = 0;
	HR(m_VertexBuffer->Lock(0, 0, (void**)&v, 0));


	//put top and bottom center vertex at the end
	v[mNumVertices - 2] = VertexPos(0, height*-0.5f, 0);//bottom center vertex
	v[mNumVertices - 1] = VertexPos(0, height*0.5f, 0);//top center vertex

	//generate section vertices
	float degreesPerSegment = 360.0f / numSegments;
	float radsPerSegment = (float)(degreesPerSegment * M_PI / 180.0f);
	float theta, x, z;
	//generate bottom vertices
	for (int i = 0; i < numSegments; i++)
	{
		theta = i*radsPerSegment;
		x = cos(theta) * radius;
		z = sin(theta) * radius;
		v[i] = VertexPos(x, height*-0.5f, z);
	}
	//generate top vertices
	int topVertexStart = numSegments;
	for (int i = 0; i < numSegments; i++)
	{
		theta = i*radsPerSegment;
		x = cos(theta) * radius;
		z = sin(theta) * radius;
		v[i + topVertexStart] = VertexPos(x, height*0.5f, z);
	}
	

	HR(m_VertexBuffer->Unlock());
}
void Primitive3D::buildCylinderIndexBuffer(IDirect3DDevice9* gd3dDevice, float height, float radius, int numSegments)
{
	mNumTriangles = numSegments * 4;//4 triangles per section

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
	int topVertexStart = numSegments;
	int topTriStart = topVertexStart * 3;
	//TODO: do last section manually (due to wrap around)
	//generate top/bottom indices
	for (int i = 0; i < numSegments-1; i++)
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
		vertIndex = numSegments - 1;
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
	for (int i = 0; i < numSegments - 1; i++)
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
		vertIndex = numSegments - 1;
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

//-----------------------------------------------------------------------------
void Primitive3D::buildSphereVertexBuffer(IDirect3DDevice9* gd3dDevice, float radius, int numSegments)
{
	//mRenderVerts = true;
	mNumVertices = numSegments * numSegments; //8 sections vertically and horizontally

	// Obtain a pointer to a new vertex buffer.
	HR(gd3dDevice->CreateVertexBuffer(mNumVertices * sizeof(VertexPos), D3DUSAGE_WRITEONLY,
		0, D3DPOOL_MANAGED, &m_VertexBuffer, 0));

	// Now lock it to obtain a pointer to its internal data, and write the
	// cylinder's vertex data.
	VertexPos* v = 0;
	HR(m_VertexBuffer->Lock(0, 0, (void**)&v, 0));


	//OpenGL tested Sphere verts, Solution 1: http://stackoverflow.com/a/13846592
	float const R = (float)(1. / (float)(numSegments - 1));
	float const S = (float)(1. / (float)(numSegments - 1));

	int vertCounter = 0;
	float x, y, z;
	for (int r = 0; r < numSegments; r++)
	{
		for (int s = 0; s < numSegments; s++)
		{
			x = cosf(2 * (float)M_PI * s * S) * sinf((float)M_PI * r * R);
			y = sinf((float)-M_PI_2 + (float)M_PI * r * R);
			z = sinf(2 * (float)M_PI * s * S) * sinf((float)M_PI * r * R);

			x *= radius;
			y *= radius;
			z *= radius;

			v[vertCounter++] = VertexPos(x, y, z);
		}
	}


	HR(m_VertexBuffer->Unlock());
}
void Primitive3D::buildSphereIndexBuffer(IDirect3DDevice9* gd3dDevice, float radius, int numSegments)
{
	//mNumTriangles = (int)pow(mPrimitive_NumSections, 2); //8 sections vertically and horizontally
	mNumTriangles = mNumVertices * 2;//2 triangles are generated for each vertex

	// Obtain a pointer to a new index buffer.
	//number of triangles times 3 to get number of indices in total
	HR(gd3dDevice->CreateIndexBuffer(mNumTriangles * 3 * sizeof(WORD), D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_IndexBuffer, 0));

	// Now lock it to obtain a pointer to its internal data, and write the
	// cylinder's index data.

	WORD* k = 0;

	HR(m_IndexBuffer->Lock(0, 0, (void**)&k, 0));


	//*Solution 1: http://stackoverflow.com/a/13846592
	int indexCounter = 0;
	for (int r = 0; r < numSegments; r++)
	{
		for (int s = 0; s < numSegments; s++)
		{
			{//Generate Index Buffer
				int curRow = r * numSegments;
				int nextRow = (r + 1) * numSegments;

				k[indexCounter++] = curRow + s;
				k[indexCounter++] = nextRow + s;
				k[indexCounter++] = nextRow + (s + 1);

				k[indexCounter++] = curRow + s;
				k[indexCounter++] = nextRow + (s + 1);
				k[indexCounter++] = curRow + (s + 1);
			}
		}
	}


	HR(m_VertexBuffer->Unlock());
}
//=============================================================================
