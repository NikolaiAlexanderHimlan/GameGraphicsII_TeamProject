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
//=============================================================================
struct IDirect3DVertexBuffer9;
struct IDirect3DIndexBuffer9;
typedef D3DXVECTOR3 Vector3f;
//=============================================================================
class BaseObject3D
{
private:
	int mNumTriangles;
	int mNumVertices;

	//Cylinder values
	int mPrimitive_NumSections = 8;//relevant to cone, cylinder, and sphere
	float mPrimitive_Height = 2.0f;//relevant to cone and cylinder
	float mPrimitive_Radius = 1.0f;//relevant to cone, cylinder, and sphere

protected:	
    D3DXMATRIX                  m_World;

	IDirect3DVertexBuffer9*     m_VertexBuffer;
	IDirect3DIndexBuffer9*      m_IndexBuffer;


protected:
    // Replace the code in the following methods
    virtual void buildDemoCubeVertexBuffer( IDirect3DDevice9* gd3dDevice );
    virtual void buildDemoCubeIndexBuffer( IDirect3DDevice9* gd3dDevice );

	virtual void buildDemoCylinderVertexBuffer( IDirect3DDevice9* gd3dDevice );
	virtual void buildDemoCylinderIndexBuffer(IDirect3DDevice9* gd3dDevice);

public:
	enum PrimitiveType
	{
		INVALID_PRIMITIVE = -1, 

		CUBE, 
		CONE, 
		CYLINDER, 
		SPHERE, 

		NUM_PRIMITIVES
	};
    BaseObject3D(void);
    ~BaseObject3D(void);

	inline int getTriangleCount() { return mNumTriangles;	};
	inline int getVertexCount() { return mNumVertices;	};

	void setWorldPosition(const Vector3f& newPosition);

    // Replace or add to the following code as you progress with the material
    virtual void Create( IDirect3DDevice9* gd3dDevice, PrimitiveType createPrimitive = CUBE );
    virtual void Render( IDirect3DDevice9* gd3dDevice, D3DXMATRIX& view, D3DXMATRIX& projection );
};
//=============================================================================
#endif // _BASE_OBJECT_3D_H

