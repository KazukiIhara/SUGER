// This
#include "Object2dSystem.h"

// MyHedder
#include "DirectXManager.h"
#include "GraphicsPipelineManager.h"

void Object2DSystem::Initialize(DirectXManager* directX, GraphicsPipelineManager* pipelineManager) {
	SetDirectXManager(directX);
	SetPipelineManager(pipelineManager);
}

void Object2DSystem::PreDraw() {
	// RootSignatureを設定。PSOに設定しているけど別途設定が必要
	directX_->GetCommandList()->SetGraphicsRootSignature(pipelineManager_->GetRootSignature(GraphicsPipelineManager::kObject2d));
	// 形状を設定。PSOに設定しているものとはまた別。同じものを設定すると考えておけば良い
	directX_->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}
