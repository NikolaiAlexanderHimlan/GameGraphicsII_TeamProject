//=============================================================================
//                              BaseMaterial
//
// Base class that contains the most intrinsic parameters to implement per model
// lighting / shaders effects.
//=============================================================================
#include "BaseMaterial.h"
#include <D3D9.h>
#include <d3dx9tex.h>
#include <d3dx9.h>
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
void BaseMaterial::LoadTexture(const std::string& filename)
{
	IDirect3DTexture9* texture;
	HR(D3DXCreateTextureFromFile(gd3dDevice, filename.c_str(), &texture));
	setTexture(texture);
}
void BaseMaterial::setTexture(IDirect3DTexture9* texture)
{
	mImageTexture = texture;
	HR(m_Effect->SetTexture(mTextureHandle, mImageTexture));
}
void BaseMaterial::ToggleTextureRender()
{
	if (mImageTexture == nullptr) return;//nothing changes if there is no valid texture

	mRenderTexture = !mRenderTexture;//switch texture rendering

	//resend the correct texture
	if (mRenderTexture) {
		HR(m_Effect->SetTexture(mTextureHandle, mImageTexture));
	}
	else {
		HR(m_Effect->SetTexture(mTextureHandle, mBlankTexture));
	}
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
	mWorldMatInvHandle = m_Effect->GetParameterByName(0, "gWorldInverseTranspose");
	m_WorldMatHandle = m_Effect->GetParameterByName(0, "gWorld");
	m_ViewerPosWHandle = m_Effect->GetParameterByName(0, "gEyePosW");
	m_LightPosWHandle = m_Effect->GetParameterByName(0, "gLightVecW");
	m_ShininessHandle = m_Effect->GetParameterByName(0, "gSpecularPower");
	m_SpecularColHandle = m_Effect->GetParameterByName(0, "gSpecularMtrl");
	mSpecularLightHandle = m_Effect->GetParameterByName(0, "gSpecularLight");
	mRenderSpecularHandle = m_Effect->GetParameterByName(0, "gRenderSpecular");
	m_DIffuseColHandle = m_Effect->GetParameterByName(0, "gDiffuseMtrl");
	mDiffuseLightHandle = m_Effect->GetParameterByName(0, "gDiffuseLight");
	mRenderDiffuseHandle = m_Effect->GetParameterByName(0, "gRenderDiffuse");
	mAmbientColorHandle = m_Effect->GetParameterByName(0, "gAmbientMtrl");
	mAmbientLightHandle = m_Effect->GetParameterByName(0, "gAmbientLight");

	mRenderTextureHandle = m_Effect->GetParameterByName(0, "gRenderTexture");
	mTextureHandle = m_Effect->GetParameterByName(0, "gTexture");

	//send null texture to start with
	HR(m_Effect->SetTexture(mTextureHandle, mBlankTexture));
}

//-----------------------------------------------------------------------------
void BaseMaterial::Render(const D3DXMATRIX& worldMat, const D3DXMATRIX& viewMat, const D3DXMATRIX& projMat, ID3DXMesh* objMesh) const
{
	HR(m_Effect->SetValue(m_LightPosWHandle, &mLightVecW, sizeof(D3DXVECTOR3)));
	HR(m_Effect->SetValue(m_DIffuseColHandle, &mDiffuseMtrl, sizeof(D3DXCOLOR)));
	HR(m_Effect->SetValue(mDiffuseLightHandle, &mDiffuseLight, sizeof(D3DXCOLOR)));
	HR(m_Effect->SetBool(mRenderDiffuseHandle, mRenderDiffuse));
	HR(m_Effect->SetValue(mAmbientColorHandle, &mAmbientMtrl, sizeof(D3DXCOLOR)));
	HR(m_Effect->SetValue(mAmbientLightHandle, &mAmbientLight, sizeof(D3DXCOLOR)));
	HR(m_Effect->SetBool(mRenderSpecularHandle, mRenderSpecular));
	HR(m_Effect->SetValue(mSpecularLightHandle, &mSpecularLight, sizeof(D3DXCOLOR)));
	HR(m_Effect->SetValue(m_SpecularColHandle, &mSpecularMtrl, sizeof(D3DXCOLOR)));
	HR(m_Effect->SetFloat(m_ShininessHandle, mSpecularPower));

	HR(m_Effect->SetBool(mRenderTextureHandle, ShouldRenderTexture()));

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
