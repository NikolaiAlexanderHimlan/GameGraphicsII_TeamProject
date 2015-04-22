/*
Author: Nikolai Alexander-Himlan & Andrew Esposito
Class: EGP-300 <Section 52>
Assignment: AdvancedTexturing
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "NormalMaterial.h"

void NormalMaterial::ConnectToEffect(ID3DXEffect* effect)
{
	__super::ConnectToEffect(effect);

	mhRenderNormalMapHandle = m_Effect->GetParameterByName(0, "gRenderNormalMap");
	mhNormalMapStrengthHandle = m_Effect->GetParameterByName(0, "gNormalPower");
	mhNormalMapHandle = m_Effect->GetParameterByName(0, "gNormalMap");
}

void NormalMaterial::LoadNormalMap(const std::string& filename)
{
	IDirect3DTexture9* normalMap;
	HR(D3DXCreateTextureFromFile(gd3dDevice, filename.c_str(), &normalMap));
	setNormalMap(normalMap);
}
void NormalMaterial::setNormalMap(IDirect3DTexture9* normaMap)
{
	clearNormalMap();
	mNormalMapTexture = normaMap;
	HR(m_Effect->SetTexture(mhNormalMapHandle, mNormalMapTexture));
}
void NormalMaterial::ToggleNormalMapRender()
{
	if (mNormalMapTexture == nullptr) return;//nothing changes if there is no valid normalMap

	mRenderNormalMap = !mRenderNormalMap;//switch normalMap rendering

	//resend the correct normalMap
	if (mRenderNormalMap) {
		HR(m_Effect->SetTexture(mhNormalMapHandle, mNormalMapTexture));
	}
	else {
		HR(m_Effect->SetTexture(mhNormalMapHandle, mBlankTexture));
	}
}

void NormalMaterial::RefreshEffectValues(const CameraView* viewCamera) const
{
	__super::RefreshEffectValues(viewCamera);

	HR(m_Effect->SetBool(mhRenderNormalMapHandle, mRenderNormalMap));
	if (mRenderNormalMap)
	{
		HR(m_Effect->SetFloat(mhNormalMapStrengthHandle, mNormalMapStrength));
	}
}

