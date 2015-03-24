#ifndef Vector3f_h__
#define Vector3f_h__
/*
Author: Nikolai Alexander-Himlan & Andrew Esposito
Class: EGP-300 <Section 52>
Assignment: Shader Materials
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include <d3dx9math.h>
#include <string>

enum AXIS
{
	X_AXIS,
	Y_AXIS,
	Z_AXIS
};

typedef D3DXVECTOR3 Vector3f;

const std::string toString(const Vector3f&);

#endif // Vector3f_h__
