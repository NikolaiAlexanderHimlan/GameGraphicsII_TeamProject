//=============================================================================
//                              Sphere3D
//
//=============================================================================
#include "Sphere3D.h"
#include "Vertex.h"
#include "../GfxStats.h"

#define _USE_MATH_DEFINES
#include <math.h>

//=============================================================================
void Sphere3D::BuildTexCoord()
{
	// D3DXCreate* functions generate vertices with position and normal data.
	// But for texturing, we also need tex-coords.
	// So clone the mesh to change the vertex format to a format with tex-coords.

	D3DVERTEXELEMENT9 elements[64];
	UINT numElements = 0;
	VertexPNT::Decl->GetDeclaration(elements, &numElements);

	ID3DXMesh* temp = 0;
	HR(mObjectMesh->CloneMesh(D3DXMESH_SYSTEMMEM, elements, gd3dDevice, &temp));

	ReleaseCOM(mObjectMesh);

	// Now generate texture coordinates for each vertex.
	VertexPNT* vertices = 0;
	HR(temp->LockVertexBuffer(0, (void**)&vertices));

	int vertCount = temp->GetNumVertices();
	bool suchens;
	for (UINT i = 0; i < temp->GetNumVertices(); ++i)
	{
		// Convert to spherical coordinates.
		D3DXVECTOR3 p = vertices[i].pos;

		float theta = atan2f(p.z, p.x);
		float phi = acosf(p.y / sqrtf(p.x*p.x + p.y*p.y + p.z*p.z));

		// Phi and theta give the texture coordinates, but are not in 
		// the range [0, 1], so scale them into that range.

		float u = theta / (2.0f*D3DX_PI);
		float v = phi / D3DX_PI;

		if (u > 1.0f || v > 1.0f || u < 0.0f || v < 0.0f)
			suchens = true;

		// Save texture coordinates.

		vertices[i].tex.x = u;
		vertices[i].tex.y = v;
	}
	HR(temp->UnlockVertexBuffer());

	// Clone back to a hardware mesh.
	HR(temp->CloneMesh(D3DXMESH_MANAGED | D3DXMESH_WRITEONLY, elements, gd3dDevice, &mObjectMesh));

	ReleaseCOM(temp);
}

//-----------------------------------------------------------------------------
/*
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
//*/
//=============================================================================
