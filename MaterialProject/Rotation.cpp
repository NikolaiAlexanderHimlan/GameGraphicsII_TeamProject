/*
Author: Nikolai Alexander-Himlan & Andrew Esposito
Class: EGP-300 <Section 52>
Assignment: Shader Materials
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "Rotation.h"

#include ".\NAH_lib\RotationMath.h"

const Rotation asRadians(const Rotation& degreesRotation)
{
	return Rotation(
		nah::DegToRad(degreesRotation.x),
		nah::DegToRad(degreesRotation.y),
		nah::DegToRad(degreesRotation.z)
		);
}
