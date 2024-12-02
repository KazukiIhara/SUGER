struct VertexShaderInput
{
    uint32_t instanceId : SV_InstanceID; // インスタンシング用
    uint32_t vertexId : SV_VertexID; // 頂点ID
};

struct VertexShaderOutput
{
    float32_t4 position : SV_POSITION; // スクリーン座標
    float32_t4 color : COLOR0; // ラインの色
};

// 3Dラインデータ
struct LineData3D
{
    float32_t3 start;
    float32_t3 end;
    float32_t4 color;
};

// 定数バッファ
cbuffer TransformBuffer : register(b0)
{
    float32_t4x4 WVP; // ワールド・ビュー・プロジェクション行列
};

// インスタンシングバッファ
StructuredBuffer<LineData3D> gLines : register(t0);