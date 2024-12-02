struct VertexShaderInput
{
    uint32_t instanceId : SV_InstanceID; // �C���X�^���V���O�p
    uint32_t vertexId : SV_VertexID; // ���_ID
};

struct VertexShaderOutput
{
    float32_t4 position : SV_POSITION; // �X�N���[�����W
    float32_t4 color : COLOR0; // ���C���̐F
};

// 3D���C���f�[�^
struct LineData3D
{
    float32_t3 start;
    float32_t3 end;
    float32_t4 color;
};

// �萔�o�b�t�@
cbuffer TransformBuffer : register(b0)
{
    float32_t4x4 WVP; // ���[���h�E�r���[�E�v���W�F�N�V�����s��
};

// �C���X�^���V���O�o�b�t�@
StructuredBuffer<LineData3D> gLines : register(t0);