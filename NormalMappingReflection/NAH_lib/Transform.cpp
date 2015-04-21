/*
Author: Nikolai Alexander-Himlan & Andrew Esposito
Class: EGP-300 <Section 52>
Assignment: Shader Materials
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "Transform.h"

#include <d3dx9math.h>

void Transform::calcRenderMatrix(D3DXMATRIX* outMatrix) const
{
	D3DXMATRIX trans, rot, scl, tempMat;

	D3DXMatrixTranslation(&trans, position.x, position.y, position.z);
	D3DXMatrixRotationYawPitchRoll(&rot, rotation.y, rotation.x, rotation.z);
	D3DXMatrixScaling(&scl, scale.x, scale.y, scale.z);

	D3DXMatrixMultiply(&tempMat, &rot, &trans);
	D3DXMatrixMultiply(outMatrix, &scl, &tempMat);
}
