#include "Barrier.h"

#include <cassert>

#include "directX/swapChain/SwapChain.h"
#include "directX/command/DirectXCommand.h"

void Barrier::Initialize(DirectXCommand* command, SwapChain* swapChain, RenderTexture* renderTexture) {
	// インスタンスをセット
	SetSwapChain(swapChain);
	SetCommand(command);
	SetRenderTexture(renderTexture);
	// タイプはトランジション
	swapChainBarrier_.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	// None
	swapChainBarrier_.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
}

void Barrier::PreDrawBarrierSwapChain() {
	// バリアを張る対象のリソース
	swapChainBarrier_.Transition.pResource = swapChian_->GetCurrentBackBufferResource();
	// 遷移前のリソースステート
	swapChainBarrier_.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
	// 遷移後のリソースステート
	swapChainBarrier_.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
	// トランジションバリアを張る
	command_->GetList()->ResourceBarrier(1, &swapChainBarrier_);
}

void Barrier::PostDrawBarrierSwapChain() {
	// 遷移前のリソースステート
	swapChainBarrier_.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
	// 遷移後の
	swapChainBarrier_.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
	// トランジションバリアを張る
	command_->GetList()->ResourceBarrier(1, &swapChainBarrier_);
}

void Barrier::SetCommand(DirectXCommand* command) {
	assert(command);
	command_ = command;
}

void Barrier::SetSwapChain(SwapChain* swapChain) {
	assert(swapChain);
	swapChian_ = swapChain;
}

void Barrier::SetRenderTexture(RenderTexture* renderTexture) {
	assert(renderTexture);
	renderTexture_ = renderTexture;
}
