//=============================================================================
//                              Cone3D
//
//=============================================================================
#include "Cone3D.h"
#include "Vertex.h"
#include "../GfxStats.h"

#define _USE_MATH_DEFINES
#include <math.h>

//=============================================================================
/*
void Cone3D::buildConeVertexBuffer(IDirect3DDevice9* gd3dDevice)
{
	mNumVertices = mNumSegments + 2; //1 vertex for each section plus a vertex in the center on the top and bottom.

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

	float degreesPerSegment = 360.0f / mNumSegments;
	float radsPerSegment = (float)(degreesPerSegment * M_PI / 180.0f);
	float theta, x, z;
	for (int i = 0; i < mNumSegments; i++)
	{
		theta = i*radsPerSegment;
		x = cos(theta) * mRadius;
		z = sin(theta) * mRadius;
		v[i] = VertexPos(x, mHeight*-0.5f, z);
	}


	HR(m_VertexBuffer->Unlock());
}
void Cone3D::buildConeIndexBuffer(IDirect3DDevice9* gd3dDevice)
{
	mNumTriangles = mNumSegments * 2;//2 triangles per section

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
	for (int i = 0; i < mNumSegments-1; i++)
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
	int lastIndex = mNumSegments - 1;
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
//*/
//=============================================================================
