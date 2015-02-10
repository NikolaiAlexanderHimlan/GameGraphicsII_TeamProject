//=============================================================================
//                              Cylinder3D
//
//=============================================================================
#ifndef _CYLINER_3D_H
#define _CYLINER_3D_H
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
class Cylinder3D
	: public BaseObject3D
{
private:
	float mHeight;
	float mRadius;
	int mNumSegments;
protected:

protected:
	virtual void buildCylinderVertexBuffer( IDirect3DDevice9* gd3dDevice );
	virtual void buildCylinderIndexBuffer( IDirect3DDevice9* gd3dDevice );
public:
    Cylinder3D(float height, float radius, int numSegments);
    ~Cylinder3D(void);

	void Create(IDirect3DDevice9* gd3dDevice);
};
//=============================================================================
#endif // _BASE_OBJECT_3D_H

