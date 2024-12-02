#include "LineGraphicsPipeline.h"

void LineGraphicsPipeline::Initialize(DirectXManager* directXManager) {
}

ID3D12RootSignature* LineGraphicsPipeline::GetRootSignature() {
	return nullptr;
}

ID3D12PipelineState* LineGraphicsPipeline::GetPipelineState(BlendMode blendMode) {
	return nullptr;
}

void LineGraphicsPipeline::SetDirectXManager(DirectXManager* directX) {
}

void LineGraphicsPipeline::CreateRootSignature() {
}

void LineGraphicsPipeline::CompileShaders() {
}

void LineGraphicsPipeline::CreateGraphicsPipelineObject() {
}

void LineGraphicsPipeline::InitializeDxCompiler() {
}

ComPtr<ID3DBlob> LineGraphicsPipeline::CompileShader(const std::wstring& filePath, const wchar_t* profile, IDxcUtils* dxcUtils, IDxcCompiler3* dxcCompiler, IDxcIncludeHandler* includeHandler) {
	return ComPtr<ID3DBlob>();
}

D3D12_BLEND_DESC LineGraphicsPipeline::BlendStateSetting(uint32_t blendModeNum) {
	return D3D12_BLEND_DESC();
}

D3D12_DEPTH_STENCIL_DESC LineGraphicsPipeline::DepthStecilDescSetting() {
	return D3D12_DEPTH_STENCIL_DESC();
}

D3D12_INPUT_LAYOUT_DESC LineGraphicsPipeline::InputLayoutSetting() {
	return D3D12_INPUT_LAYOUT_DESC();
}

D3D12_RASTERIZER_DESC LineGraphicsPipeline::RasterizerStateSetting() {
	return D3D12_RASTERIZER_DESC();
}
