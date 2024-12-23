#include "NonePostEffectPipeline.h"

#include <cassert>

void NonePostEffectPipeline::Initialize(DXGIManager* dxgi) {
}

ID3D12RootSignature* NonePostEffectPipeline::GetRootSignature() {
	return nullptr;
}

ID3D12PipelineState* NonePostEffectPipeline::GetPipelineState() {
	return nullptr;
}

void NonePostEffectPipeline::CreateRootSignature() {
}

void NonePostEffectPipeline::CompileShaders() {
}

void NonePostEffectPipeline::CreateGraphicsPipelineObject() {
}

void NonePostEffectPipeline::InitializeDxCompiler() {
}

ComPtr<ID3DBlob> NonePostEffectPipeline::CompileShader(const std::wstring& filePath, const wchar_t* profile, IDxcUtils* dxcUtils, IDxcCompiler3* dxcCompiler, IDxcIncludeHandler* includeHandler) {
	return ComPtr<ID3DBlob>();
}

D3D12_BLEND_DESC NonePostEffectPipeline::BlendStateSetting(uint32_t blendModeNum) {
	return D3D12_BLEND_DESC();
}

D3D12_DEPTH_STENCIL_DESC NonePostEffectPipeline::DepthStecilDescSetting() {
	return D3D12_DEPTH_STENCIL_DESC();
}

D3D12_INPUT_LAYOUT_DESC NonePostEffectPipeline::InputLayoutSetting() {
	return D3D12_INPUT_LAYOUT_DESC();
}

D3D12_RASTERIZER_DESC NonePostEffectPipeline::RasterizerStateSetting() {
	return D3D12_RASTERIZER_DESC();
}

void NonePostEffectPipeline::SetDXGI(DXGIManager* dxgi) {
	assert(dxgi);
	dxgi_ = dxgi;
}
