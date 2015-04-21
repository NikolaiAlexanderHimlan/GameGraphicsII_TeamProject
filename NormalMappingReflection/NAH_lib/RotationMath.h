#ifndef RotationMath_h__
#define RotationMath_h__

/*
Author: Nikolai Alexander-Himlan
Class: EPG-310 <Section 02>
Assignment: midterm
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/

#include "PrecisionMath.h"

namespace nah
{
	//namespace math {
	//TODO: CONSIDER: should the Degrees/Radians be denoted at the beginning or end of the function?
#pragma region Degrees Math
	//defined constants
#define MIN_ROTATION_DEGREES 0.0f
#define MAX_ROTATION_DEGREES 360.0f
#define HALF_ROTATION_DEGREES 180.0f
	//alternative names
#define MIN_DEGREE MIN_ROTATION_DEGREES
#define MAX_DEGREE MAX_ROTATION_DEGREES
#define HALF_DEGREE HALF_ROTATION_DEGREES
	//************************************
	// Method:    absoluteRotation_Degrees
	// FullName:  nah::math::absoluteRotation_Degrees
	// Access:    public 
	// Returns:   float
	// Parameter: float rotation
	//************************************
	/// <summary> Gets the equivalent value for a rotation in degrees between 0 and 360. </summary>
	/// <param name="degrees">A rotation value in degrees. </param>
	/// <returns> The equivalent rotation value between 0 and 360. </returns>
	static inline float absoluteRotation_Degrees(float degrees)
	{
		while(degrees < MIN_DEGREE)//check negative
			return degrees +MAX_DEGREE;//equivalent positive rotation value
		while (degrees > MAX_DEGREE)//check if greater than 360
			degrees -=MAX_DEGREE;//reduce rotation until below 360
		return degrees;//already positive
	}
	//************************************
	// Method:    oppositeRotation_Degrees
	// FullName:  nah::math::oppositeRotation_Degrees
	// Access:    public 
	// Returns:   float
	// Parameter: float degrees
	//************************************
	/// <summary> Gets the rotation value in degrees opposite of the given rotation value, accounting for negative values
	/// </summary>
	/// <param name="degrees"></param>
	/// <returns></returns>
	static inline float oppositeRotation_Degrees(float degrees)
	{
		if(degrees < MIN_DEGREE)//check negative
			return degrees +HALF_DEGREE;//+360 to make positive then -180 to get the opposite
		return degrees -HALF_DEGREE;//already positive, -180 to get the opposite
	}
	static inline float oppositeRotation_AbsDegrees(float degrees)
	{ return absoluteRotation_Degrees(oppositeRotation_Degrees(degrees));	}
#pragma endregion
#pragma region Radians Math
	//defined constants
#define MIN_ROTATION_RADIANS 0.0f
#define MAX_ROTATION_RADIANS 2.0f
#define HALF_ROTATION_RADIANS 1.0f
	//alternative names
#define MIN_RADIAN MIN_ROTATION_RADIANS
#define MAX_RADIAN MAX_ROTATION_RADIANS
#define HALF_RADIAN HALF_ROTATION_RADIANS
	static inline float absoluteRotation_Radians(float radians);
	static inline float oppositeRotation_Radians(float radians);
	static inline float oppositeRotation_AbsRadians(float radians)
	;//{ return absoluteRotation_Radians(oppositeRotation_Radians(radians));	}
#pragma endregion
#pragma region Conversion
	//make these constants so the program doesn't keep having to do the same division
	//TODO: make private/move from header to source file
	extern const double TO_RADIAN;
	extern const double TO_DEGREE;

	//TODO: find alternative shortening which obeys scope.
#define DegToRad DegreesToRadians
	static inline float DegreesToRadians(float degrees)
	{
		//trace("radical",degrees * Math.PI / 180);
		float radians = (float)(degrees * TO_RADIAN);
		return (radians);
	}
#define RadToDeg RadiansToDegrees
	static inline float RadiansToDegrees(float radians)
	{
		//trace("severity",radians * 180/Math.PI);
		float degrees = (float)(radians * TO_DEGREE);
		return (degrees);
	}
#pragma endregion

#pragma region Precision adjusted trig
	//TODO: change case to match sin, cos, tan function case
	//CONSIDER: overloaded functions instead of type indication character suffix
	static inline float SinF_Precise(const float& radians) { return LimitPrecision(sin(radians));	};
	static inline float CosF_Precise(const float& radians) { return LimitPrecision(cos(radians));	};
	static inline float TanF_Precise(const float& radians);

	static inline double SinD_Precise(const double& radians);
	static inline double CosD_Precise(const double& radians);
	static inline double TanD_Precise(const double& radians);
#pragma endregion
	//}
}
#endif // RotationMath_h__
