#ifndef PrecisionMath_h__
#define PrecisionMath_h__
/*
Author: Nikolai Alexander-Himlan
Class: EPG-425 <Section 51>
Assignment: pa 3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/

#include <cmath>

namespace nah
{
	//Handles precision
	static const double MIN_SCI_LIMIT = 1e-005;
	
	//TODO: figure out whether doing ref or value first retains more precision?
	//Will set any number less than MIN_SCI_LIMIT to 0
	static double& LimitPrecision(double& limitThis)
	{
		if (abs(limitThis) < MIN_SCI_LIMIT)
			limitThis = 0;

		return limitThis;
	}
	static double LimitPrecision(const double& limitThis)
	{
		double tempLimit = limitThis;
		return LimitPrecision(tempLimit);
	}

	//TODO: figure out whether doing ref or value first retains more precision?
	//Will set any number less than MIN_SCI_LIMIT to 0
	static float& LimitPrecision(float& limitThis)
	{
		if (abs(limitThis) < MIN_SCI_LIMIT)
			limitThis = 0;

		return limitThis;
	}
	static float LimitPrecision(const float& limitThis)
	{
		float tempLimit = limitThis;
		return LimitPrecision(tempLimit);
	}
}
#endif // PrecisionMath_h__
