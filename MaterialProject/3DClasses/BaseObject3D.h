//=============================================================================
//                              BaseObject3D
//
// Written by Adi Bar-Lev, 2013
// EGP 300-101, Graphics Programming II  - skeleton project
//
// Base class that can handle 3D rendering via Vertex and Index buffer
//=============================================================================
#ifndef _BASE_OBJECT_3D_H
#define _BASE_OBJECT_3D_H
//=============================================================================
#pragma once
//=============================================================================
#include <d3dx9.h>

#include "../d3dUtil.h"

#include "../BaseMaterial.h"
#include "../Vector3f.h"
#include "../Rotation.h"
//=============================================================================
struct IDirect3DVertexBuffer9;
struct IDirect3DIndexBuffer9;
//=============================================================================
class BaseObject3D
{
private:
    D3DXMATRIX                  m_World;

protected:	
	int mNumVertices;
	int mNumTriangles;

	ID3DXMesh*		mObjectMesh;
	BaseMaterial* mObjectMaterial;
	
	virtual void Build( IDirect3DDevice9* gd3dDevice ) = 0;

public:
    BaseObject3D(void);
    ~BaseObject3D(void);

	inline int getTriangleCount() { return mNumTriangles;	};
	inline int getVertexCount() { return mNumVertices;	};

	void setWorldPosition(const Vector3f& newPosition);
	void setWorldRotation(const Rotation& newRotation);

    // Replace or add to the following code as you progress with the material
	inline virtual void Create(IDirect3DDevice9* gd3dDevice) final {
		Build(gd3dDevice);
		mNumTriangles = mObjectMesh->GetNumFaces();
		mNumVertices = mObjectMesh->GetNumVertices();
	};
	inline void setMaterial( BaseMaterial* newMaterial ) { mObjectMaterial = newMaterial;	};
	virtual void Render( IDirect3DDevice9* gd3dDevice, D3DXMATRIX& view, D3DXMATRIX& projection ) final;
};
//=============================================================================
#endif // _BASE_OBJECT_3D_H

