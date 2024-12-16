#include "PostEffectPipelineManager.h"

// 標準C++ヘッダー
#include <cassert>
#include <format>  

// カスタムヘッダー
#include "debugTools/logger/Logger.h"  // ログ出力に使用
#include "directX/dxgi/DXGIManager.h"

void PostEffectPipelineManager::Initialize(DXGIManager* dxgi) {
}

ID3D12RootSignature* PostEffectPipelineManager::GetRootSignature(PostEffectPipelineType pipelineType) {
	return nullptr;
}

ID3D12PipelineState* PostEffectPipelineManager::GetPipelineState(PostEffectPipelineType pipelineType) {
	return nullptr;
}

void PostEffectPipelineManager::SetRootSignature(PostEffectPipelineType pipelineType) {
}

void PostEffectPipelineManager::SetPipelineState(PostEffectPipelineType pipelineType) {
}
