
struct PixelInputType
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float2 UV : TEXCOORD0;
};

sampler2D ColorSampler = sampler_state
{
    Texture = <ColorTexture>;
    FILTER = MIN_MAG_MIP_LINEAR;
    AddressU = WRAP;
    AddressV = WRAP;
};

float4 main(PixelInputType input) : COLOR
{

    // Sample the pixel color from the texture using the sampler at this texture coordinate location.
    float4 textureColor = tex2D(ColorSampler, input.UV).rgba;

    return textureColor;
}