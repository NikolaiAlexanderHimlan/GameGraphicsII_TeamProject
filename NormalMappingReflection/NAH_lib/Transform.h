#ifndef _TRANSFORM_H
#define _TRANSFORM_H
/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 0
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/
#include "../Vector3f.h"
#include "../Rotation3D.h"
#include "RotationMath.h"

class Transform
{
public:
	Vector3f position;
	//TODO: replace rotation with a quaternion
	Rotation3D rotation;//degrees
	//Rotation3D rotation;//degrees
	//CONSIDER: replace with Scale object which is essentially a Vector3fFactor to make division cheaper
	Vector3f scale;

public:
	Transform(const Vector3f& init_position = Vect3_zero, const Vector3f& init_rotation = Vect3_zero, const Vector3f& init_scale = Vect3_one);
	~Transform();

	//Getters

	//Setters
	void setScale(float newScale);

	inline void setPitchRad(float radians);
	inline void setYawRad(float radians);
	inline void setRollRad(float radians);

	//Properties
	//more efficient, only calculates the requested axes of the vector
	Vector3f getForwardVector(char axis) const;
	Vector3f getUpVector(char axis) const;
	Vector3f getRightVector(char axis) const;
	//get all axes
	inline Vector3f getForwardVector() const { return getForwardVector('a'); };
	inline Vector3f getUpVector() const { return getUpVector('a'); };
	inline Vector3f getRightVector() const { return getRightVector('a'); };

	//Modifiers
	float addPitchDeg(float degrees);
	float addYawDeg(float degrees);
	float addRoll(float degrees);
	float addPitchRad(float radians);
	float addYawRad(float radians);
	float addRollRad(float radians);

	//Calculations
	inline Rotation3D calcLookAtRotation(const Vector3f lookHere) const //calculates the necessary rotation in order to look at a given location from this location
	{
		Rotation3D lookRotation = Rotation3D(true);

		Vector3f diff = lookHere - position;
		float xzdistance = sqrt(diff.x * diff.x + diff.z * diff.z);
		lookRotation.x = (-atan2(diff.y, xzdistance)); // rotation around x
		lookRotation.y = (atan2(diff.x, diff.z)); // rotation around y
		lookRotation.z = (0); // rotation around z

		return lookRotation;
	}; 
	void calcRenderMatrix(D3DXMATRIX* outMatrix) const;

	//Actions
	inline void moveForward(float amount)	{ position += getForwardVector() * amount;	};
	inline void moveRight(float amount)		{ position += getRightVector() * amount;	};
	inline void moveUp(float amount)		{ position += getUpVector() * amount;		};

	void rotatePitch(float degrees);
	void rotateYaw(float degrees);
	void rotateRoll(float degrees);
	inline void rotateRollRight(float degrees) { return rotateRoll(degrees);	};
	inline void rotateTurnRight(float degrees) { return rotateYaw(degrees);	};
	inline void rotateTurnUp(float degrees) { return rotatePitch(degrees);	};

	inline void lookAt(const Transform& worldTransform) { rotation = calcLookAtRotation(worldTransform.position).asRadians();	};//look at the transform once

	//Type Conversions
	std::string toString(bool pos = true, bool rot = true, bool scl = true) const;
	std::string toStringMultiLine(bool pos = true, bool rot = true, bool scl = true) const;
};
#endif // Transform_h__
