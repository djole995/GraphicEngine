static float cnt = 0.1f;

struct PS_INPUT
{
	float4 position : SV_POSITION;
	//float4 interpolatedColor : COLOR;
	float2 UV : TEXCOORD2;
};

sampler2D ColorSampler = sampler_state 
{
	Texture = <ColorTexture>;
	FILTER = MIN_MAG_MIP_LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};

float4 main(PS_INPUT input) : COLOR
{
	float3 diffuseColor = tex2D(ColorSampler, input.UV).rgb;
	return float4(diffuseColor, 1);
    //return input.interpolatedColor;
}