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

