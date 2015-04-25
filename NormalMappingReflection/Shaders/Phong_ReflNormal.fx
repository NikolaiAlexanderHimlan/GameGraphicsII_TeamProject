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

uniform extern float4 gDefaultColor;

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
	AddressU  = CLAMP;
	AddressV  = CLAMP;
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
	AddressU  = CLAMP;
	AddressV  = CLAMP;
};

struct InputVS {
};

struct OutputVS {
	float4 posH		: POSITION0;
	float3 normalW	: TEXCOORD0;
	float3 posW		: TEXCOORD1;
	float2 tex0		: TEXCOORD2;
	float3 toEyeT	: TEXCOORD3;
	float3 lightDirT: TEXCOORD4;
};

OutputVS PhongVS(float3 posL	 : POSITION0, 
				float3 tangentL	 : TANGENT0, 
				float3 binormalL : BINORMAL0, 
				float3 normalL	 : NORMAL0, 
				float2 tex0		 : TEXCOORD0)
{
	// Zero out our output.
	OutputVS outVS = (OutputVS)0;

	// Build TBN-basis.
	float3x3 TBN;
	TBN[0] = tangentL;
	TBN[1] = binormalL;
	TBN[2] = normalL;

	// Matrix transforms from object space to tangent space.
	float3x3 toTangentSpace = transpose(TBN);

	// Transform world eye position to local space.
	float3 eyePosL = mul(float4(gEyePosW, 1.0f), gWorldInverseTranspose).xyz;

	// Transform local to-eye vector to tangent space.
	float3 toEyeL = eyePosL - posL;
	outVS.toEyeT = mul(toEyeL, toTangentSpace);

	float3 lightDirW = -gLightVecW;//light dir is opposite light vector
	// Transform local light direction to tangent space.
	float3 lightDirL = mul(float4(lightDirW, 0.0f), gWorldInverseTranspose).xyz;
	outVS.lightDirT  = mul(lightDirL, toTangentSpace);

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

float4 PhongPS( float3 normalW	 : TEXCOORD0,
				float3 posW		 : TEXCOORD1, 
				float2 tex0		 : TEXCOORD2,
				float3 toEyeT	 : TEXCOORD3,
				float3 lightDirT : TEXCOORD4) : COLOR
{
	// Interpolated normals can become unnormal--so normalize.
	normalW		= normalize(normalW);
	toEyeT		= normalize(toEyeT);
	lightDirT	= normalize(lightDirT);

	// Compute the vector from the vertex to the eye position.
	float3 toEyeW = normalize(gEyePosW - posW);

	// Get data from the normal map
	float3 normalT = tex2D(NormalSampler, tex0);

	// Expand from [0, 1] compressed interval to true [-1, 1] interval.
	//normalT = 2.0f*normalT - 1.0f;
	//normalT = gNormalPower* 2.0f* normalT - 1.0f;
	//normalT = gNormalPower* (2.0f* normalT - 1.0f);
	//normalT = gNormalPower * normalT - 1.0f;
	//normalT = gNormalPower * (normalT - 1.0f);
	normalT = gNormalPower * (normalT - 0.5f);
	normalT += 0.5f;
	normalT = normalize(normalT);//need unit vector for normal

	float3 normalCalc;//normal value to use for calculations
	float3 normTVal = normalT;// * gNormalPower;
	float3 normWVal = normalW * (1.0-gNormalPower);
	[flatten] if (gRenderNormalMap)
	{
		//use normal map tangent normal
		normalCalc = normalize(normTVal + normWVal);
	}
	else
		normalCalc = normalW;//use regular world normal

	// Compute Reflection (using normal map value)
	float3 r = reflect(-gLightVecW, normalCalc);
	float3 envColor = texCUBE(EnvMapSampler, r).rgb;
	float3 reflVal = envColor * gReflectBlending;
	float reflBlend = 1.0f - gReflectBlending;//amount to blend existing colors into the reflection

	// Determine how much (if any) specular light makes it into the eye.
	float t = pow(saturate(dot(r, toEyeW)), gSpecularPower);

	// Determine the diffuse light intensity that strikes the vertex.
	float s = max(dot(gLightVecW, normalCalc), 0.0f);

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

	float3 diffuse;//final color of the surface
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
		diffuse = diffuseVal + ambientVal;
		alphaVal *= gDiffuseMtrl.a;
	}
	else
	{
		diffuse = diffuseVal;
	}
	
	//Combine diffuse with pixel color
	[flatten] if (gRenderDiffuse)
	{
		pixColor = texColor * diffuse;
	}
	else
	{
		[flatten] if (gRenderTexture)
			pixColor = texColor;
		else
			pixColor = gDefaultColor;//no more multiplication, remove value of empty texture
	}

	//if diffuse and ambient are both disabled,, reflections will need to be reapplied
	[flatten] if (gRenderReflection)
	{
		//reapply reflection for each effect disabled
		[flatten] if (!gRenderDiffuse)
		{
			//if textures are also disabled, then the color should be the reflection
			[flatten] if (!gRenderTexture)
				pixColor = reflVal;
			else
				pixColor += reflVal;
		}
		[flatten] if (!gRenderAmbient)
			pixColor += reflVal;
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
