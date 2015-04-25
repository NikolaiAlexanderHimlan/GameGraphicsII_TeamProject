//=============================================================================
//                              Cylinder3D
//
//=============================================================================
#ifndef _CYLINER_3D_H
#define _CYLINER_3D_H
//=============================================================================
#pragma once
//=============================================================================
#include "BaseObject3D.h"
//=============================================================================
class Cylinder3D
	: public BaseObject3D
{
private:
	float mHeight;
	float mRadius;
	int mNumSegments;
	int mNumSplits;

	AXIS mAxis = Z_AXIS;

protected:
	//virtual void buildCylinderVertexBuffer( IDirect3DDevice9* gd3dDevice );
	//virtual void buildCylinderIndexBuffer( IDirect3DDevice9* gd3dDevice );

	inline void Build(IDirect3DDevice9* gd3dDevice) {
		HR(D3DXCreateCylinder(gd3dDevice, mRadius, mRadius, mHeight, mNumSegments, mNumSplits, &mObjectMesh, 0));
		//buildCylinderVertexBuffer( gd3dDevice );
		//buildCylinderIndexBuffer( gd3dDevice );
	};
	void BuildTexCoord() { __super::BuildTexCoord(); }; //HACK: placeholder, implement TexCoord

public:
	/// <param name="numSplits"> Number of splits along the height of the cone. </param>
	Cylinder3D(float height, float radius, int numSegments, int numSplits = 1)
		: mHeight(height), mRadius(radius), mNumSegments(numSegments), mNumSplits(numSplits) {};
	virtual ~Cylinder3D(void){};
};
//=============================================================================
#endif // _CYLINDER_3D_H

