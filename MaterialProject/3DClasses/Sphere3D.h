//=============================================================================
//                              Sphere3D
//
//=============================================================================
#ifndef _SPHERE_3D_H
#define _SPHERE_3D_H
//=============================================================================
#pragma once
//=============================================================================
#include "BaseObject3D.h"
//=============================================================================
class Sphere3D
	: public BaseObject3D
{
private:
	float mRadius;
	int mNumSegments;

protected:
	//virtual void buildSphereVertexBuffer( IDirect3DDevice9* gd3dDevice );
	//virtual void buildSphereIndexBuffer( IDirect3DDevice9* gd3dDevice );

	inline void Build( IDirect3DDevice9* gd3dDevice ) {
		HR(D3DXCreateSphere(gd3dDevice, mRadius, mNumSegments, mNumSegments, &mObjectMesh, 0));
		//buildSphereVertexBuffer( gd3dDevice );
		//buildSphereIndexBuffer( gd3dDevice );
	};
	void BuildTexCoord();

public:
	Sphere3D(float radius, int numSegments)
		: mRadius(radius), mNumSegments(numSegments) {};
	~Sphere3D(void){};
};
//=============================================================================
#endif // _SPHERE_3D_H

