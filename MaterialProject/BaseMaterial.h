//=============================================================================
//                              BaseMaterial
//
// Written by Adi Bar-Lev, 2013
// EGP 300-101, Graphics Programming II  - skeleton project
//
// Base class that contains the most intrinsic parameters to implement per model
// lighting / shaders effects.
//=============================================================================
#pragma once
#include "d3dApp.h"
//=============================================================================
class BaseMaterial
{
protected:
    ID3DXEffect*        m_Effect;               // the shader associate effect file

    //-------- Material Parameters -------
    D3DXMATRIX          m_WorldMat;
    D3DXMATRIX          m_ViewProjectionMat;

public:
    D3DXVECTOR3         m_DiffuseColor;
    D3DXVECTOR3         m_SpecularColor;
    float				m_Shininess;            // specular power

	D3DXVECTOR3 mLightVecW;
	D3DXCOLOR   mAmbientMtrl;
	D3DXCOLOR   mAmbientLight;
	D3DXCOLOR   mDiffuseMtrl;
	D3DXCOLOR   mDiffuseLight;
	D3DXCOLOR   mSpecularMtrl;
	D3DXCOLOR   mSpecularLight;
	float       mSpecularPower;

protected:
    //---------- Shader Handles ----------
    // Generic shader handles
    D3DXHANDLE          m_WorldMatHandle;    
	D3DXHANDLE			mWorldMatInvHandle;
    D3DXHANDLE          m_ViewProjectionMatHandel;

    D3DXHANDLE          m_LightPosWHandle;       // Position (spot/point) / Direction (directional)
    D3DXHANDLE          m_ViewerPosWHandle;

    // Material specific shader handles
    D3DXHANDLE          m_DIffuseColHandle;    
	D3DXHANDLE			mDiffuseLightHandle;
    D3DXHANDLE          m_SpecularColHandle;
	D3DXHANDLE			mSpecularLightHandle;
    D3DXHANDLE          m_ShininessHandle;   
	D3DXHANDLE			mAmbientColorHandle;
	D3DXHANDLE			mAmbientLightHandle;


public:
    BaseMaterial(void);
    virtual ~BaseMaterial(void);

	void LoadEffect(const std::string& filename);
    void ConnectToEffect( ID3DXEffect* effect );
    void Render( D3DXMATRIX& worldMat, D3DXMATRIX& viewProjMat ) const; 
	void Render(const D3DXMATRIX& worldMat, const D3DXMATRIX& viewMat, const D3DXMATRIX& projMat, ID3DXMesh* objMesh) const;
};
//=============================================================================

