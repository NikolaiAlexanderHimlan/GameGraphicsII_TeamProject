//=============================================================================
//                              Teapot3D
//
//=============================================================================
#ifndef _TEAPOT_3D_H
#define _TEAPOT_3D_H
//=============================================================================
#pragma once
//=============================================================================
#include "BaseObject3D.h"
//=============================================================================
class Teapot3D
	: public BaseObject3D
{
private:

protected:
	//virtual void buildTeapotVertexBuffer( IDirect3DDevice9* gd3dDevice );
	//virtual void buildTeapotIndexBuffer( IDirect3DDevice9* gd3dDevice );

	virtual void Build( IDirect3DDevice9* gd3dDevice ) {
		HR(D3DXCreateTeapot(gd3dDevice, &mObjectMesh, 0));
		//buildTeapotVertexBuffer( gd3dDevice );
		//buildTeapotIndexBuffer( gd3dDevice );
	}

public:
	Teapot3D() {};
	~Teapot3D(void){};
};
//=============================================================================
#endif // _BASE_OBJECT_3D_H

