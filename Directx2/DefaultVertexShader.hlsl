// TYPEDEFS //
//////////////

matrix worldMatrix : register(c0);
matrix viewMatrix : register(c4);
matrix projectionMatrix : register(c8);


struct VertexInputType
{
    float4 position : POSITION;
    float3 normal : NORMAL;
    float2 UV : TEXCOORD0;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float2 UV : TEXCOORD0;
};


PixelInputType main(VertexInputType input)
{
    PixelInputType output;


    output.position = mul(input.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);
   

    output.UV = input.UV;

    // Calculate the normal vector against the world matrix only.
    output.normal = mul(input.normal, (float3x3) worldMatrix);
	
    // Normalize the normal vector.
    output.normal = normalize(output.normal);

    return output;
}