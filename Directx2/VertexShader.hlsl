// TYPEDEFS //
//////////////

matrix worldMatrix : register(c0);
matrix viewMatrix : register(c4);
matrix projectionMatrix: register(c8);


struct VertexInputType
{
    float4 position : POSITION;
    float2 UV : TEXCOORD2;
   // float4 color : COLOR;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 UV : TEXCOORD1;
  //  float4 color : COLOR;
};


PixelInputType main( VertexInputType input )
{
    PixelInputType output;


    output.position = mul(input.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);

    output.UV = input.UV;
    
    return output;
}