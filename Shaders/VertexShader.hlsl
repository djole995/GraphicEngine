// TYPEDEFS //
//////////////

matrix worldMatrix : register(c0);
matrix viewMatrix : register(c4);
matrix projectionMatrix : register(c8);


struct VertexInputType
{
    float4 position : POSITION;
    float3 normal : NORMAL;
   // float4 color : COLOR;
    float2 UV : TEXCOORD0;
};

struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 UV : TEXCOORD0;
   // float4 color : COLOR;
    float3 normal : NORMAL;
    //float2 cameraPosition : NORMAL;
};


PixelInputType main(VertexInputType input)
{
    PixelInputType output;


    output.position = mul(input.position, worldMatrix);
    output.position = mul(output.position, viewMatrix);
    output.position = mul(output.position, projectionMatrix);
    float4 outputCameraPosition;

    outputCameraPosition = mul(float4(0, 0, 20, 1), worldMatrix);
    outputCameraPosition = mul(outputCameraPosition, viewMatrix);
    outputCameraPosition = mul(outputCameraPosition, projectionMatrix);
   

    output.UV = input.UV;
    //output.color = input.color;
   // output.cameraPosition = float2(outputCameraPosition.x, outputCameraPosition.y);

    // Calculate the normal vector against the world matrix only.
    output.normal = mul(input.normal, (float3x3) worldMatrix);
	
    // Normalize the normal vector.
    output.normal = normalize(output.normal);

    return output;
}