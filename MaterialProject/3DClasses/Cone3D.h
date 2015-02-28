//=============================================================================
//                              Cone3D
//
//=============================================================================
#ifndef _CONE_3D_H
#define _CONE_3D_H
//=============================================================================
#pragma once
//=============================================================================
#include "BaseObject3D.h"
//=============================================================================
class Cone3D
	: public BaseObject3D
{
private:
	float mHeight;
	float mRadius;
	int mNumSegments;
	int mNumSplits;

protected:
	//virtual void buildConeVertexBuffer( IDirect3DDevice9* gd3dDevice );
	//virtual void buildConeIndexBuffer( IDirect3DDevice9* gd3dDevice );

	inline void Build( IDirect3DDevice9* gd3dDevice ) {
		//HACK: this is stupid and inefficient, but it's how we are required to make our Cone
		HR(D3DXCreateCylinder(gd3dDevice, 0.0f, mRadius, mHeight, mNumSegments, mNumSplits, &mObjectMesh, 0));
		//buildConeVertexBuffer( gd3dDevice );
		//buildConeIndexBuffer( gd3dDevice );
	};

public:
	/// <param name="numSplits"> Number of splits along the height of the cone. </param>
	Cone3D(float height, float radius, int numSegments, int numSplits = 1)
		: mHeight(height), mRadius(radius), mNumSegments(numSegments), mNumSplits(numSplits) {};
	~Cone3D(void){};
};
//=============================================================================
#endif // _CONE_3D_H

