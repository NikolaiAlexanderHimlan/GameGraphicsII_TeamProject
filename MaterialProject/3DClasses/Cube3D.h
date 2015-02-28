//=============================================================================
//                              Cube3D
//
//=============================================================================
#ifndef _CUBE_3D_H
#define _CUBE_3D_H
//=============================================================================
#pragma once
//=============================================================================
#include "BaseObject3D.h"
//=============================================================================
class Cube3D
	: public BaseObject3D
{
private:
	float mWidth;
	float mHeight;
	float mDepth;

protected:
	//virtual void buildCubeVertexBuffer( IDirect3DDevice9* gd3dDevice );
	//virtual void buildCubeIndexBuffer( IDirect3DDevice9* gd3dDevice );

	inline void Build( IDirect3DDevice9* gd3dDevice ) {
		HR(D3DXCreateBox(gd3dDevice, mWidth, mHeight, mDepth, &mObjectMesh, 0));
		//buildCubeVertexBuffer( gd3dDevice );
		//buildCubeIndexBuffer( gd3dDevice );
	};

public:
	Cube3D(float width, float height, float depth)
		: mWidth(width), mHeight(height), mDepth(depth) {};
	~Cube3D(void){};
};
//=============================================================================
#endif // _CUBE_3D_H

