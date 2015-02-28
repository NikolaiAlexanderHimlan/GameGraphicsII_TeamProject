/*
Author:
Class: EGP-300 <Section 52>
Assignment: Shader Materials
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/

uniform extern float4x4 gWorld;
uniform extern float4x4 gWorldInvTrans;
uniform extern float4x4 gWVP;

struct InputVS {
};
struct OutputVS {
	float val1 : POSITION0;
};

OutputVS PhongVS()
{
	OutputVS outVal = (OutputVS)0;

	return outVal;
};
