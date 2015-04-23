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
	float mInnerRadius;
	float mOuterRadius;
	int mNumSections;
	int mNumRings;

protected:
	//virtual void buildTorusVertexBuffer( IDirect3DDevice9* gd3dDevice );
	//virtual void buildTorusIndexBuffer( IDirect3DDevice9* gd3dDevice );

	virtual void Build( IDirect3DDevice9* gd3dDevice ) {
		HR(D3DXCreateTorus(gd3dDevice, mInnerRadius, mOuterRadius, mNumSections, mNumRings, &mObjectMesh, 0));
		//buildTorusVertexBuffer( gd3dDevice );
		//buildTorusIndexBuffer( gd3dDevice );
	};
	void BuildTexCoord() { __super::BuildTexCoord();	}; //HACK: placeholder, implement TexCoord

public:
	Torus3D(float innerRadius, float outerRadius, int numSections, int numRings)
		: mInnerRadius(innerRadius), mOuterRadius(outerRadius), mNumSections(numSections), mNumRings(numRings) {};
	virtual ~Torus3D(void){};
};
//=============================================================================
#endif // _BASE_OBJECT_3D_H

