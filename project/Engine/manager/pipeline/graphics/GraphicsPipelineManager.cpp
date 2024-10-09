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
	// 2D用グラフィックスパイプラインを生成
	object2dGraphicsPipeline_ = std::make_unique<Object2DGraphicsPipeline>();
	object2dGraphicsPipeline_->Initialize(directXManager);
	SetRootSignature(kObject2d);
	SetGraphicsPipeline(kObject2d);

}

ID3D12RootSignature* GraphicsPipelineManager::GetRootSignature(PipelineState pipelineState) {
	return rootSignatures_[pipelineState].Get();
}

ID3D12PipelineState* GraphicsPipelineManager::GetPipelineState(PipelineState pipelineState, BlendMode blendMode) {
	return graphicsPipelineStates_[pipelineState][blendMode].Get();
}

void GraphicsPipelineManager::SetRootSignature(PipelineState pipelineState) {
	switch (pipelineState) {
	case kObject2d:
		rootSignatures_[pipelineState] = object2dGraphicsPipeline_->GetRootSignature();
		break;
	}
}

void GraphicsPipelineManager::SetGraphicsPipeline(PipelineState pipelineState) {
	switch (pipelineState) {
	case kObject2d:
		for (int mode = kBlendModeNone; mode <= kBlendModeScreen; ++mode) {
			graphicsPipelineStates_[pipelineState][mode] = object2dGraphicsPipeline_->GetPipelineState(static_cast<BlendMode>(mode));
		}
		break;
	}
}