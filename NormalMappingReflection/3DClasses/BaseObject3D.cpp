//=============================================================================
//                              BaseObject3D
//
// Written by Adi Bar-Lev, 2013
// EGP 300-101, Graphics Programming II  - skeleton project
//
// Base class that can handle 3D rendering via Vertex and Index buffer
//=============================================================================
#include "BaseObject3D.h"
#include <D3dx9math.h>
#include "Vertex.h"
#include "../GfxStats.h"
#include "../NAH_lib/CameraView.h"
//=============================================================================
BaseObject3D::BaseObject3D(void)
{
	//m_VertexBuffer = NULL;
	//m_IndexBuffer = NULL;
	mObjectMesh = nullptr;
	mObjectMaterial = nullptr;
}

//-----------------------------------------------------------------------------
BaseObject3D::~BaseObject3D(void)
{
	//ReleaseCOM(m_VertexBuffer);
	//ReleaseCOM(m_IndexBuffer);
	ReleaseCOM(mObjectMesh);
}

//-----------------------------------------------------------------------------
void BaseObject3D::setWorldPosition(const Vector3f& newPosition)
{
	//TODO: Handle relative world
	mLocalTransform.position = newPosition;
}

//-----------------------------------------------------------------------------
void BaseObject3D::setWorldRotationDegrees(const Rotation3D& newDegrees)
{
	//TODO: Handle relative world
	mLocalTransform.rotation = newDegrees.asRadians();
}

//-----------------------------------------------------------------------------
void BaseObject3D::setWorldRotationRadians(const Rotation3D& newRadians)
{
	//TODO: Handle relative world
	mLocalTransform.rotation = newRadians;
}

//-----------------------------------------------------------------------------
void BaseObject3D::BuildTexCoord()
{
	/********************
	//CODE IS IN PROGRESS OF BEING MADE TO WORK
	ID3DXMesh* tempMesh = mObjectMesh;

	// Get the vertex declaration for the NMapVertex.
	D3DVERTEXELEMENT9 elems[MAX_FVF_DECL_SIZE];
	UINT numElems = 0;
	HR(VertexNMap::Decl->GetDeclaration(elems, &numElems));

	// Clone the mesh to the NMapVertex format.
	ID3DXMesh* clonedTempMesh = 0;
	HR(tempMesh->CloneMesh(D3DXMESH_MANAGED, elems, gd3dDevice, &clonedTempMesh));

	// Now use D3DXComputeTangentFrameEx to build the TNB-basis for each vertex
	// in the mesh.  

	HR(D3DXComputeTangentFrameEx(
		clonedTempMesh, // Input mesh
		D3DDECLUSAGE_TEXCOORD, 0, // Vertex element of input tex-coords.  
		D3DDECLUSAGE_BINORMAL, 0, // Vertex element to output binormal.
		D3DDECLUSAGE_TANGENT, 0,  // Vertex element to output tangent.
		D3DDECLUSAGE_NORMAL, 0,   // Vertex element to output normal.
		0, // Options
		0, // Adjacency
		0.01f, 0.25f, 0.01f, // Thresholds for handling errors
		&mObjectMesh, // Output mesh
		0));         // Vertex Remapping

	// Done with temps.
	ReleaseCOM(tempMesh);
	ReleaseCOM(clonedTempMesh);

	//********************/

	//*
	//HACK: Default (sphere) tex coords
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
		u += 0.5f;//shift u value over from negative
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
void BaseObject3D::Render(IDirect3DDevice9* gd3dDevice, const CameraView* viewCamera) const
{
	// Update the statistics singleton class
	GfxStats::GetInstance()->addVertices(getVertexCount());
	GfxStats::GetInstance()->addTriangles(getTriangleCount());

	//Calculate the world transform matrix
	D3DXMATRIX transformationMat;
	mLocalTransform.calcRenderMatrix(&transformationMat);

	/*Vertex + Index buffer Render
	//Calculate the view and projection matrices
	D3DXMATRIX view, projection;
	viewCamera->calcViewMatrix(&view);
	viewCamera->getViewProjection(&projection);

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

	HR(m_IndexBuffer->Unlock());
	//*/

	if (mObjectMaterial == nullptr)
		mObjectMesh->DrawSubset(0);
	else //Render Material
		mObjectMaterial->Render(transformationMat, viewCamera, mObjectMesh);
}
//=============================================================================
