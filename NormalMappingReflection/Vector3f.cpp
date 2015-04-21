/*
Author: Nikolai Alexander-Himlan & Andrew Esposito
Class: EGP-300 <Section 52>
Assignment: Shader Materials
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "Vector3f.h"

#include <string>

const std::string Vect3_toString(const Vector3f& vect)
{
	return 
			"( x=" + std::to_string(vect.x) + 
			", y=" + std::to_string(vect.y) + 
			", z=" + std::to_string(vect.z) + ")";
}

