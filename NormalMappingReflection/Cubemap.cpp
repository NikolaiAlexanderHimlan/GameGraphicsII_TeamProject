/*
Author: Nikolai Alexander-Himlan & Andrew Esposito
Class: EGP-300 <Section 52>
Assignment: AdvancedTexturing
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "Cubemap.h"
#include "d3dUtil.h"

Cubemap::Cubemap(float cubeSize, const std::string& cubeTextureFilename, const std::string& shaderFilename)
	: mCubeSize(cubeSize)
	//* Cubemap subclass
	, Cube3D(cubeSize, cubeSize, cubeSize)
{
	//Create cube material
	CubeMaterial* cubeMaterial = new CubeMaterial();
	cubeMaterial->LoadEffect(shaderFilename);
	cubeMaterial->LoadCubeTexture(cubeTextureFilename);

	//disable all other effects
	cubeMaterial->ToggleDiffuse(false);
	cubeMaterial->ToggleSpecular(false);
	cubeMaterial->ToggleAmbient(false);
	
	//assign cube material
	setMaterial(cubeMaterial);
}
//*/

Cubemap::~Cubemap()
{
	//*Cubemap subclass
	deleteMaterial();
	//*/
}

