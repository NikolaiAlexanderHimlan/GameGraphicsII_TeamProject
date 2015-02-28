//=============================================================================
//                              BaseMaterial
//
// Base class that contains the most intrinsic parameters to implement per model
// lighting / shaders effects.
//=============================================================================
#include "BaseMaterial.h"
#include <D3dx9math.h>
#include "3DClasses/BaseObject3D.h"
//=============================================================================
BaseMaterial::BaseMaterial(void)
{
    m_Effect = NULL;
}

//-----------------------------------------------------------------------------
// Release shader, blah...
BaseMaterial::~BaseMaterial(void)
{
	ReleaseCOM(m_Effect);
}

//-----------------------------------------------------------------------------
void BaseMaterial::LoadEffect(const std::string& filename)
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

	m_ViewProjectionMatHandel = m_Effect->GetParameterByName(0, "gWVP");
	mWorldMatInvHandle = m_Effect->GetParameterByName(0, "gWorldInvTrans");
	m_WorldMatHandle = m_Effect->GetParameterByName(0, "gWorld");
}

//-----------------------------------------------------------------------------
void BaseMaterial::Render(const D3DXMATRIX& worldMat, const D3DXMATRIX& viewMat, const D3DXMATRIX& projMat, ID3DXMesh* objMesh)
{
	//*
	// Begin passes.
	UINT numPasses = 0;
	HR(m_Effect->Begin(&numPasses, 0));
	for (UINT i = 0; i < numPasses; ++i)
	{
		HR(m_Effect->BeginPass(i));

		D3DXMATRIX WIT;

		D3DXMatrixInverse(&WIT, 0, &worldMat);
		D3DXMatrixTranspose(&WIT, &WIT);

		HR(m_Effect->SetMatrix(m_ViewProjectionMatHandel, &(worldMat*viewMat*projMat)));
		HR(m_Effect->SetMatrix(m_WorldMatHandle, &worldMat));
		HR(m_Effect->SetMatrix(mWorldMatInvHandle, &WIT));
		HR(m_Effect->CommitChanges());
		//*/

		HR(objMesh->DrawSubset(0));

		HR(m_Effect->EndPass());
	}
	HR(m_Effect->End());
}

//=============================================================================
