/*
Author: Nikolai Alexander-Himlan & Andrew Esposito
Class: EGP-300 <Section 52>
Assignment: AdvancedTexturing
Certification of Authenticity:
I certify that this assignment is entirely my own work.
Based on the Sky object by Frank Luna
*/
#include "CubeMaterial.h"

CubeMaterial::CubeMaterial()
{
}
CubeMaterial::~CubeMaterial()
{
	clearCubeTexture();
}

void CubeMaterial::LoadCubeTexture(const std::string& filename)
{
	IDirect3DCubeTexture9* texture;
	HR(D3DXCreateCubeTextureFromFile(gd3dDevice, filename.c_str(), &texture));
	setCubeTexture(texture);
}
void CubeMaterial::setCubeTexture(IDirect3DCubeTexture9* texture)
{
	mCubeTexture = texture;
	HR(m_Effect->SetTexture(mTextureHandle, mCubeTexture));
}
void CubeMaterial::ToggleTextureRender()
{
	if (mCubeTexture == nullptr) return;//nothing changes if there is no valid texture

	mRenderTexture = !mRenderTexture;//switch texture rendering

	//resend the correct texture
	if (mRenderTexture) {
		HR(m_Effect->SetTexture(mTextureHandle, mCubeTexture));
	}
	else {
		HR(m_Effect->SetTexture(mTextureHandle, mBlankTexture));
	}
}
