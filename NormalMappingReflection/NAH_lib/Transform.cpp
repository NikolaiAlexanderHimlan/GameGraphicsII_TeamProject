/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 0
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "Transform.h"

#define _USE_MATH_DEFINES // for C++
#include <math.h>
#include <d3dx9math.h>

#include "GeneralMath.h"
#include "RotationMath.h"

const float ROTATION_LIMIT = 180.0f;//89.0 * M_PI / 180.0;

Transform::Transform(const Vector3f& init_position, const Vector3f& init_rotation, const Vector3f& init_scale)
{
	position = init_position;
	rotation = init_rotation;
	scale = init_scale;
}
Transform::~Transform()
{
}

Vector3f Transform::getForwardVector(char axis) const
{
	float forwardX = 0.0f, forwardY = 0.0f, forwardZ = 0.0f;

	//* My sourced method
	forwardX = nah::SinF_Precise(rotation.getYawRad());
	forwardY = nah::SinF_Precise(rotation.getPitchRad());
	forwardZ = nah::CosF_Precise(rotation.getPitchRad()) * nah::CosF_Precise(rotation.getYawRad());
	//*/

	Vector3f emptyOut = Vect3_zero;//because nullptr broke it
	return *D3DXVec3Normalize(&emptyOut, &Vector3f(forwardX, forwardY, forwardZ));
}
Vector3f Transform::getUpVector(char axis) const
{
	float upX = 0.0f, upY = 0.0f, upZ = 0.0f;

	//WARNING: WILL NOT WORK WITH ROLL!
	Vector3f forVect = getForwardVector();
	upX = 0.0f;//no x-axis without roll// forVect.x;
	upY = forVect.z;
	upZ = forVect.y;

	Vector3f emptyOut = Vect3_zero;//because nullptr broke it
	return *D3DXVec3Normalize(&emptyOut, &Vector3f(upX, upY, upZ));
}
Vector3f Transform::getRightVector(char axis) const
{
	float rightX=0.0f, rightY=0.0f, rightZ=0.0f;

	//WARNING: WILL NOT WORK WITH ROLL!
	Vector3f forVect = getForwardVector();
	rightX = forVect.z;
	rightY = 0.0f;//no y-axis without roll// forVect.y;
	rightZ = -forVect.x;

	Vector3f emptyOut = Vect3_zero;//because nullptr broke it
	return *D3DXVec3Normalize(&emptyOut, &Vector3f(rightX, rightY, rightZ));
}


Rotation3D Transform::calcLookAtRotation(const Vector3f lookHere) const //calculates the necessary rotation in order to look at a given location from this location
{
	Rotation3D lookRotation = Rotation3D(true);

	Vector3f diff = lookHere - position;
	float xzdistance = sqrt(diff.x * diff.x + diff.z * diff.z);
	lookRotation.x = (-atan2(diff.y, xzdistance)); // rotation around x
	lookRotation.y = (atan2(diff.x, diff.z)); // rotation around y
	lookRotation.z = (0); // rotation around z

	return lookRotation;
}
void Transform::calcRenderMatrix(D3DXMATRIX* outMatrix) const
{
	D3DXMATRIX trans, rot, scl, tempMat;

	D3DXMatrixTranslation(&trans, position.x, position.y, position.z);
	D3DXMatrixRotationYawPitchRoll(&rot, rotation.y, rotation.x, rotation.z);
	D3DXMatrixScaling(&scl, scale.x, scale.y, scale.z);

//*Original DX9 version
	D3DXMatrixMultiply(&tempMat, &rot, &trans);
	D3DXMatrixMultiply(outMatrix, &scl, &tempMat);
//*/
/*NAH_lib version
	D3DXMatrixMultiply(&tempMat, &rot, &scl);
	D3DXMatrixMultiply(outMatrix, &trans, &tempMat);
//*/
}

void Transform::setScale(float newScale)
{
	scale.x = newScale;
	scale.y = newScale;
	scale.z = newScale;
}

void Transform::rotatePitch(float degrees)
{
	float newAngle = rotation.getPitchDeg() + degrees;

	newAngle = nah::wrapFloat(newAngle, ROTATION_LIMIT, -ROTATION_LIMIT);
	rotation.setPitch(newAngle);
}

float Transform::addYawRad(float radians)
{
	rotateYaw(nah::RadToDeg(radians));
	return rotation.getYawRad();
}
void Transform::rotateYaw(float degrees)
{
	float newAngle = rotation.getYawDeg() - degrees;

	newAngle = nah::wrapFloat(newAngle, ROTATION_LIMIT, -ROTATION_LIMIT);
	rotation.setYaw(newAngle);
}
void Transform::rotateRoll(float degrees)
{
	float newAngle = rotation.getRollDeg() + degrees;

	newAngle = nah::wrapFloat(newAngle, ROTATION_LIMIT, -ROTATION_LIMIT);
	rotation.setRoll(newAngle);
}

std::string Transform::toString(bool pos /*= true*/, bool rot /*= true*/, bool scl /*= true*/) const
{
	std::string textline = "";
	if (pos)
		textline += Vect3_toString(position) + " | ";
	if (rot)
		textline += Vect3_toString(rotation) + " | ";
	if (scl)
		textline += Vect3_toString(scale);
	return textline;
}
std::string Transform::toStringMultiLine(bool pos /*= true*/, bool rot /*= true*/, bool scl /*= true*/) const
{
	std::string textline = "";
	if (pos)
		textline += Vect3_toString(position) + "\n";
	if (rot)
		textline += Vect3_toString(rotation) + "\n";
	if (scl)
		textline += Vect3_toString(scale) + "\n";
	return textline;
}


