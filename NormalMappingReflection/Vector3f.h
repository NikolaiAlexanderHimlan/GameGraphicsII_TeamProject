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

static const Vector3f Vect3_zero = Vector3f(0.0f, 0.0f, 0.0f);
static const Vector3f Vect3_one = Vector3f(1.0f, 1.0f, 1.0f);

inline static float Vect3_Distance(const Vector3f& lhs, const Vector3f& rhs)
{ return abs(D3DXVec3Length(&Vector3f(lhs - rhs)));	};

inline static Vector3f Vect3_Multiply(const Vector3f& lhs, const Vector3f& rhs)
{
	D3DXVECTOR3 mult;
	mult.x = lhs.x * rhs.x;
	mult.y = lhs.y * rhs.y;
	mult.z = lhs.z * rhs.z;
	return mult;
};
inline static Vector3f Vect3_Divide(const Vector3f& lhs, const Vector3f& rhs)
{
	D3DXVECTOR3 mult;
	mult.x = lhs.x / rhs.x;
	mult.y = lhs.y / rhs.y;
	mult.z = lhs.z / rhs.z;
	return mult;
};

const std::string Vect3_toString(const Vector3f&);

#endif // Vector3f_h__
