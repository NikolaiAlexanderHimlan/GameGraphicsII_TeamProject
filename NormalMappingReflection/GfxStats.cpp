//=============================================================================
// GfxStats.cpp by Frank Luna (C) 2005 All Rights Reserved.
// Edited by Adi Bar-Lev, 2013
//=============================================================================

#include "d3dUtil.h"
#include "d3dApp.h"
#include "GfxStats.h"
#include <tchar.h>

#include "Vector3f.h"
#include "CodingDefines.h"
#include "NAH_lib\CameraView.h"

//=============================================================================
DEFINE_SINGLETON(GfxStats);
//=============================================================================

GfxStats::GfxStats()
: mFont(0), mFPS(0.0f), mMilliSecPerFrame(0.0f), mNumTris(0), mNumVertices(0)
{
	D3DXFONT_DESC fontDesc;
	fontDesc.Height          = 18;
    fontDesc.Width           = 0;
    fontDesc.Weight          = 0;
    fontDesc.MipLevels       = 1;
    fontDesc.Italic          = false;
    fontDesc.CharSet         = DEFAULT_CHARSET;
    fontDesc.OutputPrecision = OUT_DEFAULT_PRECIS;
    fontDesc.Quality         = DEFAULT_QUALITY;
    fontDesc.PitchAndFamily  = DEFAULT_PITCH | FF_DONTCARE;
    _tcscpy_s(fontDesc.FaceName, _T("Times New Roman"));

	HR(D3DXCreateFontIndirect(gd3dDevice, &fontDesc, &mFont));
}

GfxStats::~GfxStats()
{
	ReleaseCOM(mFont);
}

void GfxStats::onLostDevice()
{
	HR(mFont->OnLostDevice());
}

void GfxStats::onResetDevice()
{
	HR(mFont->OnResetDevice());
}

void GfxStats::addVertices(DWORD n)
{
	mNumVertices += n;
}

void GfxStats::subVertices(DWORD n)
{
	mNumVertices -= n;
}

void GfxStats::addTriangles(DWORD n)
{
	mNumTris += n;
}

void GfxStats::subTriangles(DWORD n)
{
	mNumTris -= n;
}

void GfxStats::setTriCount(DWORD n)
{
	mNumTris = n;
}

void GfxStats::setVertexCount(DWORD n)
{
	mNumVertices = n;
}

void GfxStats::update(float dt)
{
	// Make static so that their values persist accross function calls.
	static float numFrames   = 0.0f;
	static float timeElapsed = 0.0f;

	// Increment the frame count.
	numFrames += 1.0f;

	// Accumulate how much time has passed.
	timeElapsed += dt;

	// Has one second passed?--we compute the frame statistics once 
	// per second.  Note that the time between frames can vary so 
	// these stats are averages over a second.
	if( timeElapsed >= 1.0f )
	{
		// Frames Per Second = numFrames / timeElapsed,
		// but timeElapsed approx. equals 1.0, so 
		// frames per second = numFrames.

		mFPS = numFrames;

		// Average time, in miliseconds, it took to render a single frame.
		mMilliSecPerFrame = 1000.0f / mFPS;

		// Reset time counter and frame count to prepare for computing
		// the average stats over the next second.
		timeElapsed = 0.0f;
		numFrames   = 0.0f;
	}
}

void GfxStats::display()
{
	// Make static so memory is not allocated every frame.
	static const int NUM_LINES = 23;
	static const int CHAR_PER_LINE = 64;
	static char buffer[CHAR_PER_LINE * NUM_LINES];

	sprintf_s(buffer, 
		"Frames Per Second = %.2f\n"
		"Milliseconds Per Frame = %.4f\n"
		"Triangle Count = %d\n"
		"Vertex Count   = %d\n"
		"Camera Distance = %.2f\n"
		"Camera Position   = %s\n"
		"Camera Rotation  = %s\n"
		"Camera Forward  = %s\n"
		"Camera Right       = %s\n"
		"Camera Up          = %s\n"

		"\nControls: \n"
		"All Lighting                           (X - Toggle)\n"
		"Ambient                   %s (E - Toggle)\n"
		"Diffuse                     %s (D - Toggle)\n"
		"Specular                   %s (C - Toggle)\n"
		"Reflection                 %s (R - Toggle)\n"
		"Textures                   %s (T - Toggle)\n"
		"Normal Map             %s (N - Toggle)\n"

		"Reflection Blending    %.1f (-/= - Adjust by 0.1)\n"
		"Normal Map Strength %.1f (A/S - Adjust by 0.1)\n"
		"Specular Coefficient   %.1f (1-7 - Select preset)\n"

		"Current target object    %i   (O - Cycle between objects)\n"
		
		, mFPS, mMilliSecPerFrame
		, mNumTris, mNumVertices
		, Vect3_Distance(Vect3_zero, mSkeletonCamera->getWorldTransform().position)
		, Vect3_toString(mSkeletonCamera->getWorldTransform().position).c_str()
		, Vect3_toString(mSkeletonCamera->getWorldTransform().rotation).c_str()
		, Vect3_toString(mSkeletonCamera->getWorldTransform().getForwardVector()).c_str()
		, Vect3_toString(mSkeletonCamera->getWorldTransform().getRightVector()).c_str()
		, Vect3_toString(mSkeletonCamera->getWorldTransform().getUpVector()).c_str()
		, EnableToStr(mAbientEnable)
		, EnableToStr(mDiffuseEnable)
		, EnableToStr(mSpecularEnable)
		, EnableToStr(mReflectionEnable)
		, EnableToStr(mTextureEnable)
		, EnableToStr(mNormalMapEnable)
		, mReflectBlend
		, mNormalStr
		, mSpecularStr
		, mCurTarget
		);

	RECT R = {5, 5, 0, 0};
	HR(mFont->DrawText(0, buffer, -1, &R, DT_NOCLIP, D3DCOLOR_XRGB(0,0,0)));
}