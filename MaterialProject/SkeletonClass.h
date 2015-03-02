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
//=============================================================================
class BaseObject3D;
class BaseMaterial;
//=============================================================================
class SkeletonClass : public D3DApp
{
private:
	const std::string ASSET_DIR = ".\\Assets\\";
	const std::string TEXTURE_FILENAME = ASSET_DIR + "Original_Utah_Teapot.bmp";
	const std::string SHADER_DIR = ".\\Shaders\\";
	const std::string GOURAD_FX_FILENAME = SHADER_DIR + "Gourad.fx";
	const std::string PHONG_FX_FILENAME = SHADER_DIR + "Phong.fx";
public:
	SkeletonClass(HINSTANCE hInstance, std::string winCaption, D3DDEVTYPE devType, DWORD requestedVP);
	~SkeletonClass();

	bool checkDeviceCaps();
	void onLostDevice();
	void onResetDevice();
	void updateScene(float dt);
	void drawScene();

	// Helper methods
	void buildViewMtx();
	void buildProjMtx();

private:
	bool mIsWireframe = false;
	bool mSpecularEnabled = true;
	bool mDiffuseEnabled = true;
	unsigned int mCurrentTarget = 3;

	float mCameraRotationY;
	float mCameraRadius;
	float mCameraHeight;
	bool mCameraInvertX = false;
	bool mCameraInvertY = false;
	bool mCameraInvertZ = false; //Zoom/Radius

	D3DXMATRIX mView;
	D3DXMATRIX mProj;

    std::vector<BaseObject3D*>      m_Objects;

	BaseMaterial*	mPhongMaterial;
	BaseMaterial*	mGouradMaterial;
	void setPhongMaterial();
	void setGouradMaterial();

	void ToggleTextureRendering();

	inline void SetTarget(unsigned int targetNum)
	{
		if (targetNum < m_Objects.size())
			mCurrentTarget = targetNum;
	};
	inline void NextTarget(void)
	{
		mCurrentTarget++;
		if (mCurrentTarget >= m_Objects.size())
			mCurrentTarget = 0;//back to start
	}
};
//=============================================================================
#endif // _SKELETON_CLASS_H_