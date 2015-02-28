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
//=============================================================================
BaseObject3D::BaseObject3D(void)
{
	//m_VertexBuffer = NULL;
	//m_IndexBuffer = NULL;
	mObjectMesh = nullptr;
	mObjectMaterial = nullptr;

    D3DXMatrixIdentity(&m_World);
}

//-----------------------------------------------------------------------------
BaseObject3D::~BaseObject3D(void)
{
	//ReleaseCOM(m_VertexBuffer);
	//ReleaseCOM(m_IndexBuffer);
	ReleaseCOM(mObjectMesh);
	delete mObjectMaterial;
}

//-----------------------------------------------------------------------------
void BaseObject3D::setWorldPosition(const Vector3f& newPosition)
{
	m_World = *D3DXMatrixTranslation(&m_World, newPosition.x, newPosition.y, newPosition.z);
}

//-----------------------------------------------------------------------------
void BaseObject3D::setWorldRotation(const Rotation& newRotation)
{
	m_World = *D3DXMatrixRotationYawPitchRoll(&m_World, newRotation.y, newRotation.x, newRotation.z);
}

//-----------------------------------------------------------------------------
void BaseObject3D::Render( IDirect3DDevice9* gd3dDevice,
    D3DXMATRIX& view, D3DXMATRIX& projection )
{
	// Update the statistics singleton class
	GfxStats::GetInstance()->addVertices(getVertexCount());
	GfxStats::GetInstance()->addTriangles(getTriangleCount());

	/*Vertex + Index buffer Render
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
		mObjectMaterial->Render(m_World, view, projection, mObjectMesh);
}
//=============================================================================
