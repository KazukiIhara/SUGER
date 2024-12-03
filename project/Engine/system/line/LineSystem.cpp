#include "LineSystem.h"

#include "manager/directX/DirectXManager.h"
#include "manager/pipeline/graphics/GraphicsPipelineManager.h"

void LineSystem::Initialize(DirectXManager* directXManager, GraphicsPipelineManager* pipelineManager) {
	SetDirectXManager(directXManager);
	SetPipelineManager(pipelineManager);
}

void LineSystem::PreDraw() {
	// RootSignatureを設定。PSOに設定しているけど別途設定が必要
	directXManager_->GetCommandList()->SetGraphicsRootSignature(pipelineManager_->GetRootSignature(kLine));
	// 形状を設定。PSOに設定しているものとはまた別。同じものを設定すると考えておけば良い
	directXManager_->GetCommandList()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
}
