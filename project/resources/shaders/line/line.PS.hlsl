#include "Line.hlsli"

struct PixelShaderOutput
{
    float32_t4 color : SV_TARGET0; // �o�͐F
};

PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;

    // ���_�J���[�����̂܂܏o��
    output.color = input.color;

    return output;
}