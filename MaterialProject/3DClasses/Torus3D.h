//=============================================================================
//                              Torus3D
//
//=============================================================================
#ifndef _TORUS_3D_H
#define _TORUS_3D_H
//=============================================================================
#pragma once
//=============================================================================
#include "BaseObject3D.h"
//=============================================================================
class Torus3D
	: public BaseObject3D
{
private:

protected:
	//virtual void buildTorusVertexBuffer( IDirect3DDevice9* gd3dDevice );
	//virtual void buildTorusIndexBuffer( IDirect3DDevice9* gd3dDevice );

	virtual void Build( IDirect3DDevice9* gd3dDevice );

public:
	Torus3D();
	~Torus3D(void);
};
//=============================================================================
#endif // _BASE_OBJECT_3D_H

