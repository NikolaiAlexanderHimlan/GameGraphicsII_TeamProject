/*
Author: Nikolai Alexander-Himlan & Andrew Esposito
Class: EGP-300 <Section 52>
Assignment: AdvancedTexturing
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "ReflectiveMaterial.h"

ReflectiveMaterial::ReflectiveMaterial()
{
}
ReflectiveMaterial::~ReflectiveMaterial()
{
}

void ReflectiveMaterial::ConnectToEffect(ID3DXEffect* effect)
{
	__super::ConnectToEffect(effect);

	mhRenderReflectionsHandle = m_Effect->GetParameterByName(0, "gRenderReflection");
	mhReflectionBlendingHandle = m_Effect->GetParameterByName(0, "gReflectBlending");;
	mhEnvironmentMapHandle = m_Effect->GetParameterByName(0, "gEnvMap");;
}
void ReflectiveMaterial::EnableEnvironmentReflection(IDirect3DTexture9* environmentTexure)
{
	HR(m_Effect->SetTexture(mhEnvironmentMapHandle, environmentTexure));
	mEnvironmentInitialized = true;
}

void ReflectiveMaterial::RefreshEffectValues() const
{
	__super::RefreshEffectValues();

	HR(m_Effect->SetBool(mhRenderReflectionsHandle, mRenderReflections));
	if(mRenderReflections)
	{
		HR(m_Effect->SetFloat(mhReflectionBlendingHandle, mReflectionBlending));
	}
}
