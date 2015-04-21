/*
Author: Nikolai Alexander-Himlan & Andrew Esposito
Class: EGP-300 <Section 52>
Assignment: Shader Materials
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "Rotation3D.h"

#include ".\NAH_lib\RotationMath.h"

const Rotation Rotation::asRadians() const
{
	return isRadians ? *this : 
		Rotation(
			nah::DegToRad(getPitch()),
			nah::DegToRad(getYaw()),
			nah::DegToRad(getRoll())
		);
}
const Rotation Rotation::asDegrees() const
{
	return !isRadians ? *this :
		Rotation(
			nah::RadToDeg(getPitch()),
			nah::RadToDeg(getYaw()),
			nah::RadToDeg(getRoll())
		);
}
