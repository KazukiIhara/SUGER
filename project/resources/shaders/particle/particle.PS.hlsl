#include "Particle.hlsli"

ConstantBuffer<Material> gMaterial : register(b0);
ConstantBuffer<ModelMaterial> gModelMaterial : register(b1);
Texture2D<float32_t4> gTexture : register(t0);
SamplerState gSampler : register(s0);


PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    float4 transformedUV = mul(float32_t4(input.texcoord, 0.0f, 1.0f), mul(gMaterial.uvTransform, gModelMaterial.uvTransform));
    float32_t4 textureColor = gTexture.Sample(gSampler, transformedUV.xy);
    
    output.color = gModelMaterial.color * gMaterial.color * textureColor * input.color;
    // output.color��a�l��0�̎���Pixel��p�p
    if (output.color.a == 0.0)
    {
        discard;
    }
    
    return output;
}
