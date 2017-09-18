
struct PixelInputType
{
    float4 position : SV_POSITION;
    float2 UV : TEXCOORD0;
	//float4 interpolatedColor : COLOR;
    float3 normal : NORMAL;
    //float2 cameraPosition : NORMAL;
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
   /* float fogFactor = (distance(float2(1366 / 2, 768 / 2), float2(input.position.x, input.position.y))) / 10;

    diffuseColor = lerp(diffuseColor, float4(0.1, 0.1, 0.1, 1.0), float4(fogFactor, fogFactor, fogFactor, fogFactor));*/
    float3 lightDirection = float3(-0.7f, -0.7f, 0.0f);
    float lightIntensity;
    float4 color;


    // Sample the pixel color from the texture using the sampler at this texture coordinate location.
    float4 textureColor = tex2D(ColorSampler, input.UV).rgba;

    // Invert the light direction for calculations.
    float3 lightDir = -lightDirection;
    float4 lightDiffuseColor = float4(1.0f, 1.0f, 0.6f, 1.0f);

    // Calculate the amount of light on this pixel.
    lightIntensity = saturate(dot(input.normal, lightDir));

    // Determine the final amount of diffuse color based on the diffuse color combined with the light intensity.
    color = saturate(lightDiffuseColor * lightIntensity);

    // Multiply the texture pixel and the final diffuse color to get the final pixel color result.
    color = color * textureColor;

    return color;
}