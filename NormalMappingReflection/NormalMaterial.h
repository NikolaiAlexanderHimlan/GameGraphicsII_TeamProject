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
	bool mRenderNormalMap = true;

protected:
	//---------- Shader Handles ----------

public:
	NormalMaterial()
	{
	};
	virtual ~NormalMaterial()
	{
	};

	void ToggleNormalMapRender();
};

