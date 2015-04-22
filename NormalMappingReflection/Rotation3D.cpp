/*
Author: Nikolai Alexander-Himlan & Andrew Esposito
Class: EGP-300 <Section 52>
Assignment: Shader Materials
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "Rotation3D.h"

#include ".\NAH_lib\RotationMath.h"

float Rotation3D::getPitchDeg() const	{ return isRadians ? nah::RadiansToDegrees(x) : x;	}
float Rotation3D::getYawDeg() const		{ return isRadians ? nah::RadiansToDegrees(y) : y;	}
float Rotation3D::getRollDeg() const	{ return isRadians ? nah::RadiansToDegrees(z) : z;	}
float Rotation3D::getPitchRad() const	{ return !isRadians ? nah::DegreesToRadians(x) : x;	}
float Rotation3D::getYawRad() const		{ return !isRadians ? nah::DegreesToRadians(y) : y;	}
float Rotation3D::getRollRad() const	{ return !isRadians ? nah::DegreesToRadians(z) : z;	}

bool Rotation3D::SwitchToDegrees(void)
{
	if (isRadians)
	{
		setPitch(getPitchDeg());
		setYaw(getYawDeg());
		setRoll(getRollDeg());
		isRadians = false;
	}
	return isRadians;
}
bool Rotation3D::SwitchToRadians(void)
{
	if (!isRadians)
	{
		setPitch(getPitchRad());
		setYaw(getYawRad());
		setRoll(getRollRad());
		isRadians = true;
	}
	return isRadians;
}

#define CALCULATE_ROTATION_LIMITS float minVal = 0.0f, maxVal, halfVal;\
{\
	if (isRadians)\
		maxVal = 2.0f;\
	else\
		maxVal = 360.0f;\
	halfVal = maxVal * 0.5f;\
	if (!zeroMin){\
		minVal -= halfVal;\
		maxVal -= halfVal;\
	}\
}\

bool Rotation3D::TruncateRotations(bool zeroMin /*= true*/)
{
	CALCULATE_ROTATION_LIMITS;

	bool changedRotation = false;
	if (x > maxVal)			{ x = maxVal; changedRotation = true; }
	else if (x < minVal)	{ x = minVal; changedRotation = true; }
	if (y > maxVal)			{ y = maxVal; changedRotation = true; }
	else if (x < minVal)	{ y = minVal; changedRotation = true; }
	if (z > maxVal)			{ z = maxVal; changedRotation = true; }
	else if (z < minVal)	{ z = minVal; changedRotation = true; }

	return changedRotation;
}
bool Rotation3D::WrapRotations(bool zeroMin /*= true*/)
{
	CALCULATE_ROTATION_LIMITS;

	bool changedRotation = false;
	if (x > maxVal)			{ x = minVal; changedRotation = true; }
	else if (x < minVal)	{ x = maxVal; changedRotation = true; }
	if (y > maxVal)			{ y = minVal; changedRotation = true; }
	else if (x < minVal)	{ y = maxVal; changedRotation = true; }
	if (z > maxVal)			{ z = minVal; changedRotation = true; }
	else if (z < minVal)	{ z = maxVal; changedRotation = true; }

	return changedRotation;
}

