/*
Author: Nikolai Alexander-Himlan & Andrew Esposito
Class: EGP-300 <Section 52>
Assignment: AdvancedTexturing
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#pragma once
#include "BaseMaterial.h"
class NormalMaterial :
	public BaseMaterial
{
public:
	//-------- Material Parameters -------
	bool		mRenderNormalMap = true;
	float		mNormalMapStrength;

protected:
	IDirect3DTexture9*	mNormalMapTexture = nullptr;

	//---------- Shader Handles ----------
	D3DXHANDLE			mhRenderNormalMapHandle;
	D3DXHANDLE			mhNormalMapStrengthHandle;
	D3DXHANDLE			mhNormalMapHandle;

	virtual void RefreshEffectValues() const;

public:
	NormalMaterial()
	{
	};
	virtual ~NormalMaterial()
	{
	};

	virtual void ConnectToEffect(ID3DXEffect* effect);

	inline bool ShouldRenderNormalMap(void) const
	{ return mRenderNormalMap && (mNormalMapTexture != nullptr);	};
	void LoadNormalMap(const std::string& filename);
	void setNormalMap(IDirect3DTexture9* texture);
	void clearNormalMap() {
		if (mNormalMapTexture != nullptr)
			ReleaseCOM(mNormalMapTexture);
	};

	void ToggleNormalMapRender();
};

