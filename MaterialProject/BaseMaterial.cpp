//=============================================================================
//                              BaseMaterial
//
// Writen by Adi Bar-Lev, 2013
// EGP 300-101, Graphics Programming II  - skeleton project
//
// Base class that contains the most intrinsic parameters to implement per model
// lighting / shaders effects.
//=============================================================================
#include "BaseMaterial.h"
//=============================================================================
BaseMaterial::BaseMaterial(void)
{
    m_Effect = NULL;
}

//-----------------------------------------------------------------------------
// Relase shader, blah...
BaseMaterial::~BaseMaterial(void)
{
}

//-----------------------------------------------------------------------------
void BaseMaterial::LoadEffect(std::string& filename)
{
	//if (std::strstr(filename.c_str(), ".fx") == nullptr) filename.append(".fx");//if given filename is not a .fx file, append .fx

	// Create the FX from a .fx file.
	ID3DXEffect* effect;
	ID3DXBuffer* errors = 0;

	HR(D3DXCreateEffectFromFile(gd3dDevice, filename.c_str(), 0, 0, D3DXSHADER_DEBUG, 0, &effect, &errors));

	if (errors)
		MessageBox(0, (char*)errors->GetBufferPointer(), 0, 0);

	ConnectToEffect(effect);
}

//-----------------------------------------------------------------------------
// Need to add here a code that will associate with your shader parameters and 
// register them.
void BaseMaterial::ConnectToEffect( ID3DXEffect* effect )
{
    m_Effect = effect;
}

//=============================================================================
