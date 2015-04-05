//=============================================================================
// sky.fx by Frank Luna (C) 2004 All Rights Reserved.
//=============================================================================

uniform extern float4x4 gWorld;
uniform extern float4x4 gWorldInverseTranspose;
uniform extern float4x4 gWVP;

uniform extern float3 gEyePosW;
uniform extern float3 gLightVecW;

uniform extern bool gRenderDiffuse;
uniform extern bool gRenderSpecular;
uniform extern bool gRenderAmbient;
uniform extern bool gRenderTexture;

uniform extern texture gTexture;

sampler EnvMapS = sampler_state
{
	Texture   = <gTexture>;
	MinFilter = LINEAR; 
	//MinFilter = Anisotropic;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	//MaxAnisotropy = 8;
	AddressU  = WRAP;
	AddressV  = WRAP;
};


void CubeVS(float3 posL : POSITION0, 
			out float4 oPosH : POSITION0, 
			out float3 oEnvTex : TEXCOORD0)
{
	// Set z = w so that z/w = 1 (i.e., cubedome always on far plane).
	oPosH = mul(float4(posL, 1.0f), gWVP).xyww;
	
	// Use cubemesh vertex position, in local space, as index into cubemap. 
	oEnvTex = posL;
}

float4 CubePS(float3 envTex : TEXCOORD0) : COLOR
{
	return texCUBE(EnvMapS, envTex);
}

technique CubeTech
{
	pass P0
	{
		vertexShader = compile vs_2_0 CubeVS();
		pixelShader  = compile ps_2_0 CubePS();
		CullMode = None;
		ZFunc = Always; // Always write cube to depth buffer
		StencilEnable = true;
		StencilFunc   = Always;
		StencilPass   = Replace;
		StencilRef	= 0; // clear to zero
	}
}

