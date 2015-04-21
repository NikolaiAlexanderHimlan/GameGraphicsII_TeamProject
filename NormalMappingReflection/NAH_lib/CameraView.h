/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 0
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#ifndef _CAMERAVIEW_H
#define _CAMERAVIEW_H

#include "TransformObject.h"

//DirectX 9 tools
struct D3DXMATRIX;
typedef D3DXMATRIX Frustum;//temporarily use matrix for frustum to contain projection matrix, should be replaced with frustum type which contains the projection matrix

class CameraView
	: public TransformObject
{
public:
	Frustum* viewFrustum;

	CameraView(const Transform& initialTransform = Transform());
	~CameraView();
	
	//Getters
	inline Frustum* getViewFrustum() const;
	void getViewProjection(D3DXMATRIX* outProj) const { *outProj = *viewFrustum;	};

	//Calculations
	void calcViewMatrix(D3DXMATRIX* outResult) const;
};

#endif
