#include "Object2D.hlsli"

ConstantBuffer<Material> gMaterial : register(b0);
Texture2D<float32_t4> gTexture : register(t0);
SamplerState gSampler : register(s0);

PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;
    float4 transformedUV = mul(float32_t4(input.texcoord, 0.0f, 1.0f), gMaterial.uvTransform);
    float32_t4 textureColor = gTexture.Sample(gSampler, transformedUV.xy);

    // Texture��a�̒l��0.5�ȉ��̎���Pixel��p�p
    if (textureColor.a <= 0.5)
    {
        discard;
    }
    
    output.color = gMaterial.color * textureColor;
    
      
    // output.color��a�l��0�̎���Pixel��p�p
    if (output.color.a == 0.0)
    {
        discard;
    }
    
    return output;
}
