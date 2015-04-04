/*
Author: Nikolai Alexander-Himlan & Andrew Esposito
Class: EGP-300 <Section 52>
Assignment: AdvancedTexturing
Certification of Authenticity:
I certify that this assignment is entirely my own work.
Based on the Sky object by Frank Luna
*/
#pragma once
#include "BaseMaterial.h"

//BaseMaterial with a cube texture instead of a regular one.
class CubeMaterial :
	public BaseMaterial
{
protected:
	IDirect3DCubeTexture9* mCubeTexture = nullptr;

public:
	CubeMaterial(void);
	virtual ~CubeMaterial();;

	//Texture
	void LoadCubeTexture(const std::string& filename);
	void setCubeTexture(IDirect3DCubeTexture9* texture);
	virtual void ToggleTextureRender();
	void clearCubeTexture()
	{
		if (mCubeTexture != nullptr)
			ReleaseCOM(mCubeTexture);
	};
};

