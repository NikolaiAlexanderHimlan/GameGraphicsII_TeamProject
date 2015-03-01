/*
Author: Nikolai Alexander-Himlan
Class: EGP-300 <Section 52>
Assignment: Shader Materials
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/

uniform extern float4x4 gWorld;
uniform extern float4x4 gWorldInverseTranspose;
uniform extern float4x4 gWVP;

uniform extern float3 gEyePosW;
uniform extern float3 gLightVecW;
uniform extern float gSpecularPower;
uniform extern float4 gSpecularMtrl;
uniform extern float4 gSpecularLight;
uniform extern float4 gDiffuseMtrl;
uniform extern float4 gDiffuseLight;
uniform extern float4 gAmbientMtrl;
uniform extern float4 gAmbientLight;

uniform extern texture gTexture;

struct InputVS {
};

struct OutputVS {
	float4 posH : POSITION0;
	float3 normalW : TEXCOORD0;
	float3 posW : TEXCOORD1;
};

OutputVS GouradVS()
{
	OutputVS outVal = (OutputVS)0;

	return outVal;
};

float4 GouradPS(float4 c : COLOR0) : COLOR
{
	return c;
}

technique GouradTech
{
	pass P0
	{
		// Specify the vertex and pixel shader associated with this pass.
		vertexShader = compile vs_2_0 GouradVS();
		pixelShader  = compile ps_2_0 GouradPS();
	}
}
