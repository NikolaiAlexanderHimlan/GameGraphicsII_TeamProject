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

uniform extern bool gRenderTexture;
uniform extern texture gTexture;

struct InputVS {
};

struct OutputVS {
	float4 posH : POSITION0;
	float3 normalW : TEXCOORD0;
	float3 posW : TEXCOORD1;
	float4 c : COLOR0;
};

OutputVS GouradVS(float3 posL : POSITION0, float3 normalL : NORMAL0)
{
	OutputVS outVS = (OutputVS)0;
	// Transform normal to world space.
	outVS.normalW = mul(float4(normalL, 0.0f),
	gWorldInverseTranspose).xyz;
	outVS.normalW = normalize(outVS.normalW);
	// Transform vertex position to world space.
	outVS.posW = mul(float4(posL, 1.0f), gWorld).xyz;
	// Transform to homogeneous clip space.
	outVS.posH = mul(float4(posL, 1.0f), gWVP);

	//Color calculation
	// Compute the vector from the vertex to the eye position.
	float3 toEye = normalize(gEyePosW - outVS.posW);
	// Compute the reflection vector.
	float3 r = reflect(-gLightVecW, outVS.normalW);
	// Determine how much (if any) specular light makes it
	// into the eye.
	float t = pow(max(dot(r, toEye), 0.0f), gSpecularPower);
	// Determine the diffuse light intensity that strikes the vertex.
	float s = max(dot(gLightVecW, outVS.normalW), 0.0f);
	// Compute the ambient, diffuse, and specular terms separately.
	float3 spec = t*(gSpecularMtrl*gSpecularLight).rgb;
	float3 diffuse = s*(gDiffuseMtrl*gDiffuseLight).rgb;
	float3 ambient = (gAmbientMtrl*gAmbientLight).xyz;
	// Sum all the terms together and copy over the diffuse alpha.
	outVS.c = float4(ambient + diffuse + spec, gDiffuseMtrl.a);

	// Done--return the output.
	return outVS;
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
