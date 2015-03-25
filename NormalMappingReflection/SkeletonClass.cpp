//=============================================================================
//                          SkeletonClass.cpp
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
#include "DirectInput.h"
#include <crtdbg.h>
#include "GfxStats.h"
#include <list>

#include "SkeletonClass.h"
#include "3DClasses\BaseObject3D.h"
#include "3DClasses\Vertex.h"
#include "3DClasses\Cube3D.h"
#include "3DClasses\Cone3D.h"
#include "3DClasses\Cylinder3D.h"
#include "3DClasses\Sphere3D.h"
#include "3DClasses\Torus3D.h"
#include "3DClasses\Teapot3D.h"
#include "Color.h"
//=============================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
				   PSTR cmdLine, int showCmd)
{
	// Enable run-time memory check for debug builds.
	#if defined(DEBUG) | defined(_DEBUG)
		_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	#endif

	SkeletonClass app(hInstance, "Exercise Skeleton Project", D3DDEVTYPE_HAL, D3DCREATE_HARDWARE_VERTEXPROCESSING);
	gd3dApp = &app;

	DirectInput di(DISCL_NONEXCLUSIVE|DISCL_FOREGROUND, DISCL_NONEXCLUSIVE|DISCL_FOREGROUND);
	gDInput = &di;

	return gd3dApp->run();
}

SkeletonClass::SkeletonClass(HINSTANCE hInstance, std::string winCaption, D3DDEVTYPE devType, DWORD requestedVP)
: D3DApp(hInstance, winCaption, devType, requestedVP)
{
	if(!checkDeviceCaps())
	{
		MessageBox(0, "checkDeviceCaps() Failed", 0, 0);
		PostQuitMessage(0);
	}

	InitAllVertexDeclarations();

	mCameraRadius    = 10.0f;
	mCameraRotationY = 1.2 * D3DX_PI;
	mCameraHeight    = 5.0f;

	//Create skybox
	mSkyboxMaterial = new BaseMaterial();
	mSkyboxMaterial->LoadEffect(PHONG_FX_FILENAME);
	mSkyboxMaterial->LoadTexture(SKYBOX_TEXTURE_FILENAME);
	mSkyboxMaterial->mLightVecW = D3DXVECTOR3(0.0, 0.0f, -1.0f);
	mSkyboxMaterial->mDiffuseMtrl = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	//mSkyboxMaterial->mDiffuseMtrl = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	mSkyboxMaterial->mDiffuseLight = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	mSkyboxMaterial->mAmbientMtrl = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	mSkyboxMaterial->mAmbientLight = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
	mSkyboxMaterial->mSpecularMtrl = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	mSkyboxMaterial->mSpecularLight = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	mSkyboxMaterial->mSpecularPower = 8.0f;
	mSkybox = new Cube3D(1.0f, 1.0f, 1.0f);
	mSkybox->Create(gd3dDevice);

	//create materials
	mPhongMaterial = new BaseMaterial();
	mPhongMaterial->LoadEffect(PHONG_FX_FILENAME);
	mPhongMaterial->LoadTexture(TEXTURE_FILENAME);
	mGouradMaterial = new BaseMaterial();
	mGouradMaterial->LoadEffect(GOURAD_FX_FILENAME);
	mGouradMaterial->LoadTexture(TEXTURE_FILENAME);

	//set Phong lighting data
	mPhongMaterial->mLightVecW = D3DXVECTOR3(0.0, 0.0f, -1.0f);
	mPhongMaterial->mDiffuseMtrl = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	//mPhongMaterial->mDiffuseMtrl = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	mPhongMaterial->mDiffuseLight = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	mPhongMaterial->mAmbientMtrl = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	mPhongMaterial->mAmbientLight = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
	mPhongMaterial->mSpecularMtrl = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	mPhongMaterial->mSpecularLight = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	mPhongMaterial->mSpecularPower = 8.0f;
	//set Gourad lighting data
	mGouradMaterial->mLightVecW = D3DXVECTOR3(0.0, 0.0f, -1.0f);
	mGouradMaterial->mDiffuseMtrl = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	mGouradMaterial->mDiffuseLight = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	mGouradMaterial->mAmbientMtrl = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	mGouradMaterial->mAmbientLight = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.0f);
	mGouradMaterial->mSpecularMtrl = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	mGouradMaterial->mSpecularLight = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	mGouradMaterial->mSpecularPower = 8.0f;
	
	// create objects
	BaseObject3D* addObject;

	addObject = new Cube3D(1.0f, 1.0f, 1.0f);
	addObject->Create( gd3dDevice );
	//addObject->setWorldPosition(Vector3f(0.0f, 0.0f, 0.0f));
	m_Objects.push_back( addObject );

	addObject = new Cone3D(2.0f, 1.0f, 8);
	addObject->Create( gd3dDevice );
	//addObject->setWorldPosition(Vector3f(-5.0f, -5.0f, 0.0f));
	addObject->setWorldRotationDegrees(Rotation(90.0f, 0.0f, 0.0f));
	m_Objects.push_back(addObject);

	addObject = new Cylinder3D(2.0f, 1.0f, 8);
	addObject->Create( gd3dDevice );
	//addObject->setWorldPosition(Vector3f(0.0f, -5.0f, -5.0f));
	addObject->setWorldRotationDegrees(Rotation(90.0f, 0.0f, 0.0f));
	m_Objects.push_back(addObject);

	addObject = new Sphere3D(1.0f, 8);
	addObject->Create( gd3dDevice );
	//addObject->setWorldPosition(Vector3f(5.0f, 5.0f, 5.0f));
	m_Objects.push_back(addObject);

	addObject = new Torus3D(0.5f, 1.0f, 8, 8);
	addObject->Create(gd3dDevice);
	//addObject->setWorldPosition(Vector3f(-5.0f, 5.0f, 5.0f));
	m_Objects.push_back(addObject);

	addObject = new Teapot3D();
	addObject->Create(gd3dDevice);
	//addObject->setWorldPosition(Vector3f(5.0f, 5.0f, -5.0f));
	m_Objects.push_back(addObject);

	setPhongMaterial();
	//setGouradMaterial();

	onResetDevice();
}

SkeletonClass::~SkeletonClass()
{
    GfxStats::DeleteInstance();

    for ( unsigned int obj=0 ; obj<m_Objects.size() ; obj++ )
        delete m_Objects[obj];
    m_Objects.clear();

	delete mPhongMaterial;
	mPhongMaterial = nullptr;

	delete mGouradMaterial;
	mGouradMaterial = nullptr;

	delete mSkybox;
	mSkybox = nullptr;

	delete mSkyboxMaterial;
	mSkyboxMaterial = nullptr;

	DestroyAllVertexDeclarations();
}

bool SkeletonClass::checkDeviceCaps()
{
	return true;
}

void SkeletonClass::onLostDevice()
{
	GfxStats::GetInstance()->onLostDevice();
}

void SkeletonClass::onResetDevice()
{
	GfxStats::GetInstance()->onResetDevice();

	// The aspect ratio depends on the backbuffer dimensions, which can 
	// possibly change after a reset.  So rebuild the projection matrix.
	buildProjMtx();
}

void SkeletonClass::updateScene(float dt)
{
	// Reset the statistics for the scene - each object will add to it.
	GfxStats::GetInstance()->setVertexCount(0);
	GfxStats::GetInstance()->setTriCount(0);
	GfxStats::GetInstance()->update(dt);

	// Get snapshot of input devices.
	gDInput->poll();

	// Check input.
	// Check inverts
	if (gDInput->keyPress(DIK_C))
		mCameraInvertY = !mCameraInvertY;
	if (gDInput->keyPress(DIK_X))
		mCameraInvertX = !mCameraInvertX;
	if (gDInput->keyPress(DIK_Z))
		mCameraInvertZ = !mCameraInvertZ;

	if( gDInput->keyDown(DIK_Y) )
		mCameraRadius	+= 25.0f * dt * ((mCameraInvertZ) ? 1.0f : -1.0f);
	if (gDInput->keyDown(DIK_H))
		mCameraRadius	-= 25.0f * dt * ((mCameraInvertZ) ? 1.0f : -1.0f);

	//Toggle render properties
	if (gDInput->keyPress(DIK_D))
	{
		//Toggle Diffuse
		mPhongMaterial->ToggleDiffuse();
		mGouradMaterial->ToggleDiffuse();
	}
	if (gDInput->keyPress(DIK_O))
		NextTarget(); //Switch between objects
	if (gDInput->keyPress(DIK_S))
	{
		//Toggle Specular
		mPhongMaterial->ToggleSpecular();
		mGouradMaterial->ToggleSpecular();
	}
	if (gDInput->keyPress(DIK_T))
		ToggleTextureRendering(); //Toggle Textures
	if (gDInput->keyPress(DIK_W))
		mIsWireframe = !mIsWireframe; // Toggle Wireframe

	//Switch object materials
	if (gDInput->keyPress(DIK_G))
		setGouradMaterial();
	if (gDInput->keyPress(DIK_P))
		setPhongMaterial();

	//Set target based on number key
	if (gDInput->keyPress(DIK_1))	SetTarget(0);
	if (gDInput->keyPress(DIK_2))	SetTarget(1);
	if (gDInput->keyPress(DIK_3))	SetTarget(2);
	if (gDInput->keyPress(DIK_4))	SetTarget(3);
	if (gDInput->keyPress(DIK_5))	SetTarget(4);
	if (gDInput->keyPress(DIK_6))	SetTarget(5);
	if (gDInput->keyPress(DIK_7))	SetTarget(6);
	if (gDInput->keyPress(DIK_8))	SetTarget(7);
	if (gDInput->keyPress(DIK_9))	SetTarget(8);
	if (gDInput->keyPress(DIK_0))	SetTarget(9);

	// Divide by 50 to make mouse less sensitive. 
	mCameraRotationY	+= gDInput->mouseDX() / 100.0f * ((mCameraInvertX) ? -1.0f : 1.0f);
	mCameraHeight		+= gDInput->mouseDY() / 25.0f * ((mCameraInvertY) ? 1.0f : -1.0f);
	mCameraRadius		+= gDInput->mouseDZ() / 25.0f * ((mCameraInvertZ) ? 1.0f : -1.0f);

	// If we rotate over 360 degrees, just roll back to 0
	if( fabsf(mCameraRotationY) >= 2.0f * D3DX_PI ) 
		mCameraRotationY = 0.0f;

	// Don't let radius get too small.
	if( mCameraRadius < 5.0f )
		mCameraRadius = 5.0f;

	// The camera position/orientation relative to world space can 
	// change every frame based on input, so we need to rebuild the
	// view matrix every frame with the latest changes.
	buildViewMtx();
}


void SkeletonClass::drawScene()
{
	// Clear the backbuffer and depth buffer.
	HR(gd3dDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0));

	HR(gd3dDevice->BeginScene());

    // Set render states for the entire scene here:
	if (mIsWireframe) {
		HR(gd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME));
	} else {
		HR(gd3dDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID));
	}

	//mSkybox->setWorldPosition(getCameraLocation());
	mSkybox->setWorldPosition(Vector3f(-5.0f, -5.0f, 0.0f));
	mSkybox->Render(gd3dDevice, mView, mProj);

	/*
    // Render all the objects
    for ( unsigned int obj=0 ; obj<m_Objects.size() ; obj++ )
    {
        m_Objects[obj]->Render( gd3dDevice, mView, mProj );
    }
	//*/
	// Render the current target
	m_Objects[mCurrentTarget]->Render( gd3dDevice, mView, mProj );

    // display the render statistics
    GfxStats::GetInstance()->display();

	HR(gd3dDevice->EndScene());

	// Present the backbuffer.
	HR(gd3dDevice->Present(0, 0, 0, 0));
}

void SkeletonClass::buildViewMtx()
{
	float x = mCameraRadius * cosf(mCameraRotationY);
	float z = mCameraRadius * sinf(mCameraRotationY);
	D3DXVECTOR3 pos(x, mCameraHeight, z);
	D3DXVECTOR3 target(m_Objects[mCurrentTarget]->getLocalTransform().position);
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(&mView, &pos, &target, &up);

	GfxStats::GetInstance()->setCameraPosition(pos);
}

void SkeletonClass::buildProjMtx()
{
	float w = (float)md3dPP.BackBufferWidth;
	float h = (float)md3dPP.BackBufferHeight;
	D3DXMatrixPerspectiveFovLH(&mProj, D3DX_PI * 0.25f, w/h, 1.0f, 5000.0f);
}

void SkeletonClass::setPhongMaterial()
{
	for (size_t i = 0; i < m_Objects.size(); i++)
		if (mPhongMaterial != m_Objects[i]->getMaterial())
			m_Objects[i]->setMaterial(mPhongMaterial);
}
void SkeletonClass::setGouradMaterial()
{
	for (size_t i = 0; i < m_Objects.size(); i++)
		if (mGouradMaterial != m_Objects[i]->getMaterial())
			m_Objects[i]->setMaterial(mGouradMaterial);
}

void SkeletonClass::ToggleTextureRendering()
{
	mPhongMaterial->ToggleTextureRender();
	mGouradMaterial->ToggleTextureRender();
}
