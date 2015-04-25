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
/*Custom Cone TexCoords
void Cone3D::BuildTexCoord()
{
	// D3DXCreate* functions generate vertices with position 
	// and normal data.  But for texturing, we also need
	// tex-coords.  So clone the mesh to change the vertex
	// format to a format with tex-coords.

	D3DVERTEXELEMENT9 elements[64];
	UINT numElements = 0;
	VertexPNT::Decl->GetDeclaration(elements, &numElements);

	ID3DXMesh* temp = 0;
	HR(mObjectMesh->CloneMesh(D3DXMESH_SYSTEMMEM,
		elements, gd3dDevice, &temp));

	ReleaseCOM(mObjectMesh);

	// Now generate texture coordinates for each vertex.
	VertexPNT* vertices = 0;
	HR(temp->LockVertexBuffer(0, (void**)&vertices));

	// We need to get the height of the cylinder we are projecting the
	// vertices onto.  That height depends on which axis the client has
	// specified that the cylinder lies on.  The height is determined by 
	// finding the height of the bounding cylinder on the specified axis.

	D3DXVECTOR3 maxPoint(-FLT_MAX, -FLT_MAX, -FLT_MAX);
	D3DXVECTOR3 minPoint(FLT_MAX, FLT_MAX, FLT_MAX);

	for (UINT i = 0; i < temp->GetNumVertices(); ++i)
	{
		D3DXVec3Maximize(&maxPoint, &maxPoint, &vertices[i].pos);
		D3DXVec3Minimize(&minPoint, &minPoint, &vertices[i].pos);
	}

	float a = 0.0f;
	float b = 0.0f;
	float h = 0.0f;
	switch (mAxis)
	{
	case X_AXIS:
		a = minPoint.x;
		b = maxPoint.x;
		h = b - a;
		break;
	case Y_AXIS:
		a = minPoint.y;
		b = maxPoint.y;
		h = b - a;
		break;
	case Z_AXIS:
		a = minPoint.z;
		b = maxPoint.z;
		h = b - a;
		break;
	}


	// Iterate over each vertex and compute its texture coordinate.

	for (UINT i = 0; i < temp->GetNumVertices(); ++i)
	{
		// Get the coordinates along the axes orthogonal to the
		// axis the cylinder is aligned with.

		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
		switch (mAxis)
		{
		case X_AXIS:
			x = vertices[i].pos.y;
			z = vertices[i].pos.z;
			y = vertices[i].pos.x;
			break;
		case Y_AXIS:
			x = vertices[i].pos.x;
			z = vertices[i].pos.z;
			y = vertices[i].pos.y;
			break;
		case Z_AXIS:
			x = vertices[i].pos.x;
			z = vertices[i].pos.y;
			y = vertices[i].pos.z;
			break;
		}

		// Convert to cylindrical coordinates.

		float theta = atan2f(z, x);
		float y2 = y - b; // Transform [a, b]-->[-h, 0]

		// Transform theta from [0, 2*pi] to [0, 1] range and
		// transform y2 from [-h, 0] to [0, 1].

		float u = theta / (2.0f*D3DX_PI);
		float v = y2 / -h;

		// Save texture coordinates.

		vertices[i].tex.x = u;
		u += 0.5f;//shift u value over from negative
		vertices[i].tex.y = v;
	}

	HR(temp->UnlockVertexBuffer());

	// Clone back to a hardware mesh.
	HR(temp->CloneMesh(D3DXMESH_MANAGED | D3DXMESH_WRITEONLY,
		elements, gd3dDevice, &mObjectMesh));

	ReleaseCOM(temp);
}
//*/

//-----------------------------------------------------------------------------
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
