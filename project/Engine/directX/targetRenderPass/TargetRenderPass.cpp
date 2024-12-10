#include "TargetRenderPass.h"

#include <cassert>

#include "directX/swapChain/SwapChain.h"

void TargetRenderPass::Initialize(DirectXCommand* command,SwapChain* swapChain) {
	SetCommand(command);
	SetSwapChain(swapChain);
}

void TargetRenderPass::SetRenderTarget() {
	
}

void TargetRenderPass::ClearRenderTarget() {}

void TargetRenderPass::SetCommand(DirectXCommand* command) {
	assert(command);
	command_ = command;
}

void TargetRenderPass::SetSwapChain(SwapChain* swapChain) {
	assert(swapChain);
	swapChain_ = swapChain;
}
