// TYPEDEFS //
//////////////

matrix worldMatrix : register(c0);
matrix viewMatrix : register(c4);
matrix projectionMatrix: register(c8);


struct VertexInputType
{
    float4 position : POSITION;
    float2 normal : NORMAL;
    float4 color : COLOR;
    float2 UV : TEXCOORD0;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 UV : TEXCOORD0;
    float4 color : COLOR;
};


PixelInputType main( VertexInputType input )
{
    PixelInputType output;


    output.position = mul(input.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);

    output.UV = input.UV;
    output.color = input.color;
    
    return output;
}