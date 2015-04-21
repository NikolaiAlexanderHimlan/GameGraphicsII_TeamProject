/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 0
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "CameraView.h"

#include <d3dx9math.h>

CameraView::CameraView(const Transform& initialTransform /*= Transform()*/)
{
	setLocalTransform(initialTransform);
	viewFrustum = new Frustum();
}
CameraView::~CameraView()
{
	delete viewFrustum;
}

void CameraView::calcViewMatrix(D3DXMATRIX* outViewMat) const
{
	getWorldTransform().calcRenderMatrix(outViewMat);
	D3DXMATRIX tempMatrix;
	float determ = D3DXMatrixDeterminant(outViewMat);
	D3DXMatrixInverse(&tempMatrix, &determ, outViewMat);
	*outViewMat = tempMatrix;

	/*
	D3DXVECTOR3 pos = getWorldTransform().position;
	D3DXVECTOR3 target = D3DXMATRIX();
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(outViewMat, &pos, &target, &up);
	//*/
}
