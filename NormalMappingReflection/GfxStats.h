//=============================================================================
// GfxStats.h by Frank Luna (C) 2005 All Rights Reserved.
//
// Class used for keeping track of and displaying the frames rendered
// per second, milliseconds per frame, and vertex and triangle counts.

// Edited by Adi Bar-Lwv, 2013
//=============================================================================

#ifndef GFX_STATS_H
#define GFX_STATS_H

#include <d3dx9.h>
#include "d3dUtil.h"

#include "Vector3f.h"
#include "Rotation3D.h"

class GfxStats
{
	DECLARE_SINGLETON(GfxStats);

public:
	Vector3f mCameraPos;
	Rotation3D mCameraRot;
	bool mAbientEnable;
	bool mDiffuseEnable;
	bool mSpecularEnable;
	bool mReflectionEnable;
	bool mTextureEnable;
	bool mNormalMapEnable;
	float mReflectBlend;
	float mNormalStr;
	float mSpecularStr;
	int mCurTarget;

	~GfxStats();

	void onLostDevice();
	void onResetDevice();

	void addVertices(DWORD n);
	void subVertices(DWORD n);
	void addTriangles(DWORD n);
	void subTriangles(DWORD n);

	void setTriCount(DWORD n);
	void setVertexCount(DWORD n);

	void setCameraPosition(const Vector3f& pos) { mCameraPos = pos;	};

	void update(float dt);
	void display();

private:
	// Prevent copying
	GfxStats(const GfxStats& rhs);
	GfxStats& operator=(const GfxStats& rhs);
	
private:
	ID3DXFont* mFont;
	float mFPS;
	float mMilliSecPerFrame;
	DWORD mNumTris;
	DWORD mNumVertices;
};
#endif // GFX_STATS_H