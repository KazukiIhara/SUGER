#include "Barrier.h"

#include <cassert>

#include "directX/swapChain/SwapChain.h"
#include "directX/command/DirectXCommand.h"

void Barrier::Initialize(DirectXCommand* command, SwapChain* swapChain) {
	SetSwapChain(swapChain);
	SetCommand(command);
}

void Barrier::PreDrawBarrierSwapChain() {
	// 今回のバリアはトランジション
	barrier_.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	// None
	barrier_.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	// バリアを張る対象のリソース
	barrier_.Transition.pResource = swapChian_->GetCurrentBuckBufferResource();
	// 遷移前のリソースステート
	barrier_.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
	// 遷移後のリソースステート
	barrier_.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
	// トランジションバリアを張る
	command_->GetList()->ResourceBarrier(1, &barrier_);
}

void Barrier::PostDrawBarrierSwapChain() {

}

void Barrier::SetCommand(DirectXCommand* command) {
	assert(command);
	command_ = command;
}

void Barrier::SetSwapChain(SwapChain* swapChain) {
	assert(swapChain);
	swapChian_ = swapChain;
}
