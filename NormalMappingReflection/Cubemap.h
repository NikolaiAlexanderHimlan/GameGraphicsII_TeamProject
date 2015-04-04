/*
Author: Nikolai Alexander-Himlan & Andrew Esposito
Class: EGP-300 <Section 52>
Assignment: AdvancedTexturing
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#pragma once
#include "Vector3f.h"
#include "3DClasses/Cube3D.h"
#include "CubeMaterial.h"

class Cubemap
	: public Cube3D
{
	float mCubeSize;

	inline CubeMaterial* getCubeMaterial() const { return dynamic_cast<CubeMaterial*>(mObjectMaterial);	};

public:
	Vector3f position;

	Cubemap(float cubeSize, const std::string& cubeTextureFilename, const std::string& shaderDirectory);
	virtual ~Cubemap();

	/*Cubemap own object
	DWORD getNumTriangles();
	DWORD getNumVertices();

	void Render( IDirect3DDevice9* gd3dDevice, D3DXMATRIX& view, D3DXMATRIX& projection ) const;
	//*/
};

