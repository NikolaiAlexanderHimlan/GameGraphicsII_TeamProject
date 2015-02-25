//=============================================================================
//                              Sphere3D
//
// Written by Adi Bar-Lev, 2013
// EGP 300-101, Graphics Programming II  - skeleton project
//=============================================================================
#include "Sphere3D.h"
#include "Vertex.h"
#include "GfxStats.h"

#define _USE_MATH_DEFINES
#include <math.h>

//=============================================================================
Sphere3D::Sphere3D(float radius, int numSegments)
	: mRadius(radius), mNumSegments(numSegments)
{
	m_VertexBuffer = NULL;
	m_IndexBuffer = NULL;

	D3DXMatrixIdentity(&m_World);
}

//-----------------------------------------------------------------------------
Sphere3D::~Sphere3D(void)
{
	ReleaseCOM(m_VertexBuffer);
	ReleaseCOM(m_IndexBuffer);
}

//-----------------------------------------------------------------------------
void Sphere3D::buildObjectBuffers(IDirect3DDevice9* gd3dDevice)
{
	buildSphereVertexBuffer( gd3dDevice );
	buildSphereIndexBuffer( gd3dDevice );
}

//-----------------------------------------------------------------------------
void Sphere3D::buildSphereVertexBuffer(IDirect3DDevice9* gd3dDevice)
{
	//mRenderVerts = true;
	mNumVertices = mNumSegments * mNumSegments; //8 sections vertically and horizontally

	// Obtain a pointer to a new vertex buffer.
	HR(gd3dDevice->CreateVertexBuffer(mNumVertices * sizeof(VertexPos), D3DUSAGE_WRITEONLY,
		0, D3DPOOL_MANAGED, &m_VertexBuffer, 0));

	// Now lock it to obtain a pointer to its internal data, and write the
	// cylinder's vertex data.
	VertexPos* v = 0;
	HR(m_VertexBuffer->Lock(0, 0, (void**)&v, 0));


	//OpenGL tested Sphere verts, Solution 1: http://stackoverflow.com/a/13846592
	float const R = (float)(1. / (float)(mNumSegments - 1));
	float const S = (float)(1. / (float)(mNumSegments - 1));

	int vertCounter = 0;
	float x, y, z;
	for (int r = 0; r < mNumSegments; r++)
	{
		for (int s = 0; s < mNumSegments; s++)
		{
			x = cosf(2 * (float)M_PI * s * S) * sinf((float)M_PI * r * R);
			y = sinf((float)-M_PI_2 + (float)M_PI * r * R);
			z = sinf(2 * (float)M_PI * s * S) * sinf((float)M_PI * r * R);

			x *= mRadius;
			y *= mRadius;
			z *= mRadius;

			v[vertCounter++] = VertexPos(x, y, z);
		}
	}


	HR(m_VertexBuffer->Unlock());
}
void Sphere3D::buildSphereIndexBuffer(IDirect3DDevice9* gd3dDevice)
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
	for (int r = 0; r < mNumSegments-1; r++)
	{
		for (int s = 0; s < mNumSegments-1; s++)
		{
			{//Generate Index Buffer
				int curRow = r * mNumSegments;
				int nextRow = (r + 1) * mNumSegments;

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
