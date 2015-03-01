#ifndef Transform_h__
#define Transform_h__
/*
Author: Nikolai Alexander-Himlan & Andrew Esposito
Class: EGP-300 <Section 52>
Assignment: Shader Materials
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "Vector3f.h"
#include "Rotation.h"

struct D3DXMATRIX;
class Transform
{
public:
	Vector3f position;
	Rotation rotation;
	Vector3f scale;

	Transform(
		const Vector3f& pos = Vector3f(0.0f, 0.0f, 0.0f), 
		const Rotation& rot = Rotation(0.0f, 0.0f, 0.0f), 
		const Vector3f& scl = Vector3f(1.0f, 1.0f, 1.0f))
		: position(pos), rotation(rot), scale(scl) {};

	void calcRenderMatrix(D3DXMATRIX* outMatrix) const;
};
#endif // Transform_h__
