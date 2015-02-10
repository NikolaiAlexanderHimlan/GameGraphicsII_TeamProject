//=============================================================================
//                              Sphere3D
//
//=============================================================================
#ifndef _SPHERE_3D_H
#define _SPHERE_3D_H
//=============================================================================
#pragma once
//=============================================================================
#include <d3dx9.h>

#include "../d3dUtil.h"

#include "BaseObject3D.h"
//=============================================================================
struct IDirect3DVertexBuffer9;
struct IDirect3DIndexBuffer9;
typedef D3DXVECTOR3 Vector3f;
//=============================================================================
class Sphere3D
	: public BaseObject3D
{
private:
	float mRadius;
	int mNumSegments;
protected:

protected:
	virtual void buildSphereVertexBuffer( IDirect3DDevice9* gd3dDevice );
	virtual void buildSphereIndexBuffer( IDirect3DDevice9* gd3dDevice );
public:
    Sphere3D(float radius, int numSegments);
    ~Sphere3D(void);

	void Create(IDirect3DDevice9* gd3dDevice);
};
//=============================================================================
#endif // _BASE_OBJECT_3D_H

