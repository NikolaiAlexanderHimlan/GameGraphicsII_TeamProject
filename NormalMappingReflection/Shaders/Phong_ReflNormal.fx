/*
Author: Nikolai Alexander-Himlan & Andrew Esposito
Class: EGP-300 <Section 52>
Assignment: AdvancedTexturing
Certification of Authenticity:
I certify that this assignment is entirely my own work.
*/

uniform extern float4x4 gWorld;
uniform extern float4x4 gWorldInverseTranspose;
uniform extern float4x4 gWVP;

uniform extern float3 gEyePosW;
uniform extern float3 gLightVecW;

uniform extern bool gRenderDiffuse;
uniform extern bool gRenderSpecular;
uniform extern bool gRenderAmbient;
uniform extern bool gRenderReflection;
uniform extern bool gRenderTexture;
uniform extern bool gRenderNormalMap;

uniform extern float gSpecularPower;
uniform extern float4 gSpecularMtrl;
uniform extern float4 gSpecularLight;
uniform extern float4 gDiffuseMtrl;
uniform extern float4 gDiffuseLight;
uniform extern float4 gAmbientMtrl;
uniform extern float4 gAmbientLight;
uniform extern float gReflectBlending;
uniform extern float gNormalPower;//strength of the normal mapping

uniform extern texture gTexture;
uniform extern texture gNormalMap;
uniform extern texture gEnvMap;//the texture to use for enviornment reflections

sampler TextureSampler = sampler_state
{
	Texture = <gTexture>;
	MinFilter = Anisotropic;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	MaxAnisotropy = 8;
	AddressU  = WRAP;
    AddressV  = WRAP;
};
sampler NormalSampler = sampler_state
{
	Texture = <gNormalMap>;
	MinFilter = ANISOTROPIC;
	MaxAnisotropy = 8;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU  = WRAP;
    AddressV  = WRAP;
};
sampler EnvMapSampler = sampler_state
{
	Texture = <gEnvMap>;
	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
	AddressU  = WRAP;
    AddressV  = WRAP;
};

struct InputVS {
};

struct OutputVS {
	float4 posH		: POSITION0;
	float3 normalW	: TEXCOORD0;
	float3 posW		: TEXCOORD1;
	float2 tex0		: TEXCOORD2;
};

OutputVS PhongVS(float3 posL : POSITION0, float3 normalL : NORMAL0, float2 tex0 : TEXCOORD0)
{
	// Zero out our output.
	OutputVS outVS = (OutputVS)0;
	
	// Transform normal to world space.
	outVS.normalW = mul(float4(normalL, 0.0f), gWorldInverseTranspose).xyz;
	outVS.normalW = normalize(outVS.normalW);
	
	// Transform vertex position to world space.
	outVS.posW = mul(float4(posL, 1.0f), gWorld).xyz;

	// Transform to homogeneous clip space.
	outVS.posH = mul(float4(posL, 1.0f), gWVP);

	//**********USED FOR TEXTURE DISPLAY
	// Pass on texture coordinates to be interpolated in
	// rasterization.
	outVS.tex0 = tex0;
	//**********

	// Done--return the output.
	return outVS;
}

float4 PhongPS(float3 normalW : TEXCOORD0, float3 posW : TEXCOORD1, float2 tex0 : TEXCOORD2) : COLOR
{
	// Interpolated normals can become unnormal--so normalize.
	normalW = normalize(normalW);
	
	// Compute the vector from the vertex to the eye position.
	float3 toEye = normalize(gEyePosW - posW);
	
	// Compute Reflection
	float3 r = reflect(-gLightVecW, normalW);
	float3 envColor = texCUBE(EnvMapSampler, r).rgb;
	float3 reflVal = envColor * gReflectBlending;
	float reflBlend = 1.0f - gReflectBlending;//amount to blend existing colors into the reflection
	
	// Determine how much (if any) specular light makes it into the eye.
	float t = pow(max(dot(r, toEye), 0.0f), gSpecularPower);
	
	// Determine the diffuse light intensity that strikes the vertex.
	float s = max(dot(gLightVecW, normalW), 0.0f);
	
	// Compute the ambient, diffuse, and specular terms separately.
	float3 ambientVal = (gAmbientMtrl*gAmbientLight).xyz;
	float3 diffuseVal = s*(gDiffuseMtrl*gDiffuseLight).rgb;
	float3 specVal = t*(gSpecularMtrl*gSpecularLight).rgb;

	//Combine the reflection into the lighting values
	[flatten] if (gRenderReflection)
	{
		ambientVal *= reflBlend;
		ambientVal += reflVal;
		diffuseVal *= reflBlend;
		diffuseVal += reflVal;
	}

	float3 texColor;//color of the texture at this coord
	float3 pixColor;//final pixel color
	float alphaVal;//final pixel alpha

	//initialize the texture color
	[flatten] if (gRenderTexture)
	{
		texColor = tex2D(TextureSampler, tex0).rgb;
		alphaVal = tex2D(TextureSampler, tex0).a;//TODO: store sample to be more efficient?
	}
	else
	{
		texColor = float3(1.0f,1.0f,1.0f); //1.0f should not affect the diffuse
		alphaVal = 1.0f;//TODO: 1.0f = full pixel alpha?
	}
	
	//combine ambient into diffuse
	[flatten] if (gRenderAmbient)
	{
		diffuseVal = diffuseVal + ambientVal;
		alphaVal *= gDiffuseMtrl.a;
	}
	else
	{
		diffuseVal = diffuseVal;
	}
	
	//Combine diffuse with pixel color
	[flatten] if (gRenderDiffuse)
	{
		pixColor = texColor * diffuseVal;
	}
	else
	{
		pixColor = texColor;
	}

	//combine specular into the pixel color
	[flatten] if (gRenderSpecular)
	{
		pixColor += specVal;
	}
	else
	{
		pixColor = pixColor;
	}

	// copy over the diffuse alpha and return the pixel color
	return float4(pixColor, alphaVal);
}

technique PhongTech
{
    pass P0
    {
        // Specify the vertex and pixel shader associated with this pass.
        vertexShader = compile vs_2_0 PhongVS();
        pixelShader  = compile ps_2_0 PhongPS();
    }
}
