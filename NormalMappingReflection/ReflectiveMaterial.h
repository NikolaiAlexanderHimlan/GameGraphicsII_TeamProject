/*
Author: Nikolai Alexander-Himlan & Andrew Esposito
Class: EGP-300 <Section 52>
Assignment: AdvancedTexturing
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#pragma once
#include "NormalMaterial.h"
class ReflectiveMaterial :
	public NormalMaterial
{
	bool		mEnvironmentInitialized = false;
public:
	bool		mRenderReflections = true;
	float		mReflectionBlending;

protected:
	//---------- Shader Handles ----------
	D3DXHANDLE	mhRenderReflectionsHandle;
	D3DXHANDLE	mhReflectionBlendingHandle;
	D3DXHANDLE	mhEnvironmentMapHandle;

	virtual void RefreshEffectValues() const;

public:

	ReflectiveMaterial();
	virtual ~ReflectiveMaterial();

	virtual void ConnectToEffect(ID3DXEffect* effect);
	void EnableEnvironmentReflection(IDirect3DCubeTexture9* environmentTexure);

	void ToggleReflection() { ToggleReflection(!mRenderReflections);	};
	void ToggleReflection(bool enabled) { mRenderReflections = enabled && mEnvironmentInitialized;	};
};

