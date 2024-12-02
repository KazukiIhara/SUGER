#include "Line.hlsli"

ConstantBuffer<Camera> gCamera : register(b0);
StructuredBuffer<LineData3D> gLines : register(t0);


VertexShaderOutput main(VertexShaderInput input)
{
    VertexShaderOutput output;

    // ���_�C���f�b�N�X�Ɋ�Â��Ďn�_/�I�_���v�Z
    LineData3D lineData = gLines[input.instanceId];
    float3 position = (input.vertexId == 0) ? lineData.start : lineData.end;

    // ���[���h�ϊ�
    output.position = mul(float4(position, 1.0f), gCamera.viewProjection);

    output.color = lineData.color;
    return output;
}