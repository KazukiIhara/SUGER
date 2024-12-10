#include "Renderer.h"

#include <cassert>

#include "directX/swapChain/SwapChain.h"

void Renderer::Initialize(DirectXCommand* command,SwapChain* swapChain) {
	SetCommand(command);
	SetSwapChain(swapChain);
}

void Renderer::SetRenderTarget() {
	
}

void Renderer::ClearRenderTarget() {}

void Renderer::SetCommand(DirectXCommand* command) {
	assert(command);
	command_ = command;
}

void Renderer::SetSwapChain(SwapChain* swapChain) {
	assert(swapChain);
	swapChain_ = swapChain;
}
