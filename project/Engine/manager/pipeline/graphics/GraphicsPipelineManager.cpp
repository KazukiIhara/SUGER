// This
#include "GraphicsPipelineManager.h"

// C++
#include <cassert>
#include <format>

// DirectX
#pragma comment(lib,"dxcompiler.lib")

// MyHedder
#include "debugTools/logger/Logger.h"
#include "manager/directX/DirectXManager.h"

void GraphicsPipelineManager::Initialize(DirectXManager* directXManager) {
	// DxCommonのインスタンスをセット
	SetDirectXCommon(directXManager);


}

ID3D12RootSignature* GraphicsPipelineManager::GetRootSignature(PipelineState pipelineState) {
	return rootSignatures_[pipelineState].Get();
}

ID3D12PipelineState* GraphicsPipelineManager::GetPipelineState(PipelineState pipelineState, BlendMode blendMode) {
	return graphicsPipelineStates_[pipelineState][blendMode].Get();
}

void GraphicsPipelineManager::SetDirectXCommon(DirectXManager* directX) {
	directX_ = directX;
}