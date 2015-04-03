/*
Author: Nikolai Alexander-Himlan & Andrew Esposito
Class: EGP-300 <Section 52>
Assignment: AdvancedTexturing
Certification of Authenticity:
I certify that this assignment is entirely my own work.
Based on the Sky object by Frank Luna
*/
#include "Cubemap.h"
#include "d3dUtil.h"

Cubemap::Cubemap(float cubeSize, const std::string& cubeTextureFilename, const std::string& shaderFilename)
	: mCubeSize(cubeSize)
//* Cubemap as its own object
{
	HR(D3DXCreateBox(gd3dDevice, mCubeSize, mCubeSize, mCubeSize, &mCubeModel, 0));
	HR(D3DXCreateCubeTextureFromFile(gd3dDevice, cubeTextureFilename.c_str(), &mCubeTexture));

	ID3DXBuffer* errors = 0;
	HR(D3DXCreateEffectFromFile(gd3dDevice, shaderFilename.c_str(), 0, 0, 0, 0, &mCubeEffect, &errors));
	if (errors)
		MessageBox(0, (char*)errors->GetBufferPointer(), 0, 0);

	mhTechnique = mCubeEffect->GetTechniqueByName("CubeTech");
	mhWVP = mCubeEffect->GetParameterByName(0, "gWVP");
	mhTexture = mCubeEffect->GetParameterByName(0, "gEnvMap");

	// Set effect parameters that do not vary.
	HR(mCubeEffect->SetTechnique(mhTechnique));
	HR(mCubeEffect->SetTexture(mhTexture, mCubeTexture));
}
//*/
	/* Cubemap subclass
	, Cube3D(mCubeSize, mCubeSize, mCubeSize)
{
	BaseMaterial* cubeMaterial = new BaseMaterial();
	cubeMaterial->LoadEffect(shaderFilename);
	cubeMaterial->LoadTexture(cubeTextureFilename);
	//disable all other effects
	cubeMaterial->ToggleDiffuse(false);
	cubeMaterial->ToggleSpecular(false);
	cubeMaterial->ToggleAmbient(false);
}
//*/

Cubemap::~Cubemap()
{
	//*Cubemap own object
	ReleaseCOM(mCubeModel);
	ReleaseCOM(mCubeTexture);
	ReleaseCOM(mCubeEffect);
	//*/
}

DWORD Cubemap::getNumTriangles()
{
	return mCubeModel->GetNumFaces();
}

DWORD Cubemap::getNumVertices()
{
	return mCubeModel->GetNumVertices();
}

void Cubemap::Render(IDirect3DDevice9* gd3dDevice, D3DXMATRIX& view, D3DXMATRIX& projection) const
{
	D3DXMATRIX W;
	D3DXVECTOR3 p = position;
	D3DXMatrixTranslation(&W, p.x, p.y, p.z);
	HR(mCubeEffect->SetMatrix(mhWVP, &(W*view*projection)));

	// Begin passes.
	UINT numPasses = 0;
	HR(mCubeEffect->Begin(&numPasses, 0));
	HR(mCubeEffect->BeginPass(0));
	HR(mCubeModel->DrawSubset(0));
	HR(mCubeEffect->EndPass());
	HR(mCubeEffect->End());
}

