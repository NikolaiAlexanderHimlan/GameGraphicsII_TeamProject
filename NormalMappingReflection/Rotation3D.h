#ifndef Rotation_h__
#define Rotation_h__
/*
Author: Nikolai Alexander-Himlan & Andrew Esposito
Class: EGP-300 <Section 52>
Assignment: Shader Materials
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "Vector3f.h"

class Rotation
	: public Vector3f
{
	bool isRadians = false;
public:
	Rotation(float pitch, float yaw, float roll)
		: Vector3f(pitch, yaw, roll) {};

	//Getters
	float getPitch() const { return x;	};
	float getYaw() const { return y;	};
	float getRoll() const { return z;	};

	const Rotation asDegrees(void) const;
	const Rotation asRadians(void) const;
};
#endif // Rotation_h__
