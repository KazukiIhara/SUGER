#include "Line.hlsli"

PixelShaderOutput main(VertexShaderOutput input)
{
    PixelShaderOutput output;

    // ���_�J���[�����̂܂܏o��
    output.color = input.color;

    return output;
}