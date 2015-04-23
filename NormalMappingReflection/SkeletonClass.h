//=============================================================================
//                          SkeletonClass.h
//
// Adopted from CubeDemo.cpp by Frank Luna (C) 2005 All Rights Reserved.
//
// Edited and changed by Adi Bar-Lev, 2013
// EGP-300-101 - Computer Graphics II, Spring 2013.
//
// This project creates a skeleton workspace and base classes for the student to be 
// able to start working with sample classes and develop evolve it according to the 
// given exercises
//
// Controls: Use mouse to orbit and zoom; use the 'W' and 'S' keys to 
//           alter the height of the camera.
//=============================================================================
#ifndef _SKELETON_CLASS_H
#define _SKELETON_CLASS_H
//=============================================================================
#pragma once
//=============================================================================
#include "d3dApp.h"

#include <vector>

#include "Vector3f.h"
//=============================================================================
class BaseObject3D;
class BaseMaterial;
class Cubemap;
class ReflectiveMaterial;
class CameraView;
//=============================================================================
class SkeletonClass : public D3DApp
{
private:
	//Directories
	const std::string ASSET_DIR = ".\\Assets\\";
	const std::string SHADER_DIR = ".\\Shaders\\";

	//Textures
	const std::string TEXTURE_FILENAME = ASSET_DIR + "Original_Utah_Teapot.bmp";
	const std::string NORMALMAP_FILENAME = ASSET_DIR + "Original_Utah_Teapot_NRM.png";
	const std::string SKYBOX_TEXTURE_FILENAME = ASSET_DIR + "cubeMap.dds";

	//Shaders
	const std::string GOURAD_FX_FILENAME = SHADER_DIR + "Gourad.fx";
	const std::string PHONG_FX_FILENAME = SHADER_DIR + "Phong.fx";
	const std::string ADVANCED_FX_FILENAME = SHADER_DIR + "Phong_ReflNormal.fx";
	const std::string CUBEMAP_FX_FILENAME = SHADER_DIR + "Cubemap.fx";

	//Shader adjust amounts
	const float REFL_BLEND_AMOUNT = 0.1f;
	const float NORMAL_STR_AMOUNT = 0.1f;
	const float SPECULAR_COEF_AMOUNT = 1.0f;

public:
	SkeletonClass(HINSTANCE hInstance, std::string winCaption, D3DDEVTYPE devType, DWORD requestedVP);
	~SkeletonClass();

	bool checkDeviceCaps();
	void onLostDevice();
	void onResetDevice();
	void updateScene(float dt);

	//Rendering
	bool mIsWireframe = false;

	//Set the material for all objects
	void setPhongMaterial();
	void setGouradMaterial();
	void setAdvancedMaterial();

	//Rendering Toggle functions (to toggle rendering for all materials)
	void ToggleDiffuseRendering(); //Toggle Diffuse rendering
	void ToggleSpecularRendering(); //Toggle Specular rendering
	void ToggleAmbientRendering();
	void ToggleReflectivity();
	void ToggleTextureRendering();
	void ToggleNormalMapRendering();

	void drawScene();

	// Helper methods
	void buildViewMtx();
	void buildProjMtx();

private:
	bool mCameraInvertX = false;
	bool mCameraInvertY = false;
	bool mCameraInvertZ = false; //Zoom/Radius
	Vector3f mCamStartPos = Vector3f(0.0f, 5.0f, -10.0f);
	CameraView* mViewCamera;

	//World/Environment Data
	Cubemap* mSkybox;

	//Material Data
	BaseMaterial* mPhongMaterial;
	BaseMaterial* mGouradMaterial;
	ReflectiveMaterial* mAdvancedMaterial;
	BaseMaterial* getCurrentMaterial() const;

	//Objects
	std::vector<BaseObject3D*> m_Objects;
	unsigned int mCurrentTarget = 3;
	inline void SetTarget(unsigned int targetNum)
	{
		if (targetNum < m_Objects.size())
			mCurrentTarget = targetNum;
		GfxStats::GetInstance()->mCurTarget = mCurrentTarget;
	};
	inline void NextTarget(void)
	{
		mCurrentTarget++;
		if (mCurrentTarget >= m_Objects.size())
			mCurrentTarget = 0;//back to start
		GfxStats::GetInstance()->mCurTarget = mCurrentTarget;
	};

protected:
	void InitializeGfxStatValues();

	void UpdateInputs(float dt);
	void UpdateCamera(float dt);

	//Adjust Material properties
	void AddReflectionBlend(float blendAmount);
	void AddNormalMapStrength(float normalAmount);
	void AddSpecularCoefficient(float specularAmount);
	void SetSpecularCoefficient(float specularAmount);
};
//=============================================================================
#endif // _SKELETON_CLASS_H_