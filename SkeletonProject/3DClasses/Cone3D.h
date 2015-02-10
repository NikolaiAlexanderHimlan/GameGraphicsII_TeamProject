//=============================================================================
//                              Primitive3D
//
//=============================================================================
#ifndef _PRIMITIVE_3D_H
#define _PRIMITIVE_3D_H
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
class Primitive3D
	: public BaseObject3D
{
private:

protected:

protected:
	virtual void buildConeVertexBuffer( IDirect3DDevice9* gd3dDevice, float height, float radius, int numSegments );
	virtual void buildConeIndexBuffer( IDirect3DDevice9* gd3dDevice, float height, float radius, int numSegments );

	virtual void buildCylinderVertexBuffer( IDirect3DDevice9* gd3dDevice, float height, float radius, int numSegments );
	virtual void buildCylinderIndexBuffer( IDirect3DDevice9* gd3dDevice, float height, float radius, int numSegments );

	virtual void buildSphereVertexBuffer( IDirect3DDevice9* gd3dDevice, float radius, int numSegments );
	virtual void buildSphereIndexBuffer( IDirect3DDevice9* gd3dDevice, float radius, int numSegments );
public:
    Primitive3D(void);
    ~Primitive3D(void);

    // Replace or add to the following code as you progress with the material
	inline void CreatePrimitive_Cube(IDirect3DDevice9* gd3dDevice)
	{
		buildDemoCubeVertexBuffer( gd3dDevice );
		buildDemoCubeIndexBuffer( gd3dDevice );
	};
	inline void CreatePrimitive_Cone( IDirect3DDevice9* gd3dDevice, float height, float radius, int numSegments )
	{
		buildConeVertexBuffer( gd3dDevice, height, radius, numSegments );
		buildConeIndexBuffer( gd3dDevice, height, radius, numSegments );
	};
	inline void CreatePrimitive_Cylinder( IDirect3DDevice9* gd3dDevice, float height, float radius, int numSegments )
	{
		buildCylinderVertexBuffer( gd3dDevice, height, radius, numSegments );
		buildCylinderIndexBuffer( gd3dDevice, height, radius, numSegments );
	};
	inline void CreatePrimitive_Sphere( IDirect3DDevice9* gd3dDevice, float radius, int numSegments )
	{
		buildSphereVertexBuffer( gd3dDevice, radius, numSegments );
		buildSphereIndexBuffer( gd3dDevice, radius, numSegments );
	};
};
//=============================================================================
#endif // _BASE_OBJECT_3D_H

