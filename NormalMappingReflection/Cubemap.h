/*
Author: Nikolai Alexander-Himlan & Andrew Esposito
Class: EGP-300 <Section 52>
Assignment: AdvancedTexturing
Certification of Authenticity:
I certify that this assignment is entirely my own work.
Based on the Sky object by Frank Luna
*/
#pragma once
#include "d3dApp.h"
#include "Vector3f.h"

class Cubemap
{
	float mCubeSize;
	ID3DXMesh* mCubeModel;
	IDirect3DCubeTexture9* mCubeTexture;
	ID3DXEffect* mCubeEffect;

	//FX handles
	D3DXHANDLE mhTechnique;
	D3DXHANDLE mhTexture;
	D3DXHANDLE mhWVP;

public:
	Vector3f position;

	Cubemap(float cubeSize, const std::string& cubeTextureFilename, const std::string& shaderDirectory);
	~Cubemap();

	DWORD getNumTriangles();
	DWORD getNumVertices();

	void Render( IDirect3DDevice9* gd3dDevice, D3DXMATRIX& view, D3DXMATRIX& projection ) const;
};

