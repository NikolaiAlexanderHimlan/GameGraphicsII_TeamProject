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

class Rotation3D
	: public Vector3f
{
	bool isRadians = false;
public:
	Rotation3D(float pitch = 0.0f, float yaw = 0.0f, float roll = 0.0f, bool isRad = false)
		: Vector3f(pitch, yaw, roll), isRadians(isRad) {};
	explicit Rotation3D(bool isRad) : Vector3f(0.0f, 0.0f, 0.0f), isRadians(isRad) {};
	Rotation3D(const Rotation3D& rot) : Vector3f((Vector3f)rot), isRadians(rot.isRadians) {};
	Rotation3D(const Vector3f& vect) : Vector3f(vect) {};//copy constructor for parent class

	//Getters
	float getPitch() const { return x;	};
	float getYaw() const { return y;	};
	float getRoll() const { return z;	};

	inline float getPitch(bool asDegrees) const	{ return asDegrees ? getPitchDeg()	: getPitchRad();	};
	inline float getYaw(bool asDegrees) const		{ return asDegrees ? getYawDeg() : getYawRad(); };
	inline float getRoll(bool asDegrees) const		{ return asDegrees ? getRollDeg() : getRollRad(); };

	//Setters
	inline void setPitch(float angle) { x = angle;	};
	inline void setYaw(float angle) { y = angle;	};
	inline void setRoll(float angle) { z = angle;	};

	//Calculations
	//Degrees
	float getPitchDeg() const;
	float getYawDeg() const;
	float getRollDeg() const;
	//Radians
	float getPitchRad() const;
	float getYawRad() const;
	float getRollRad() const;

	inline const Rotation3D asDegrees(void) const { return isRadians ? *this : Rotation3D(*this).SwitchToRadians();	};
	inline const Rotation3D asRadians(void) const { return !isRadians ? *this : Rotation3D(*this).SwitchToDegrees();	};

	//Actions
	bool SwitchToDegrees(void);
	bool SwitchToRadians(void);
	//@param zeroMin Is the minimum value 0 or the negative half rotation?
	bool TruncateRotations(bool zeroMin = true);//limit rotations to the min and max
	bool WrapRotations(bool zeroMin = true);//wrap rotation values around
};
#endif // Rotation_h__
