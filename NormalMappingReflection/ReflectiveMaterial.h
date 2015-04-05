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
public:
	bool		mRenderReflections = true;

protected:
	//---------- Shader Handles ----------

public:

	ReflectiveMaterial();
	virtual ~ReflectiveMaterial();

	void ToggleReflections() { ToggleReflections(!mRenderReflections); };
	void ToggleReflections(bool enabled) { mRenderReflections = enabled;	};
};

