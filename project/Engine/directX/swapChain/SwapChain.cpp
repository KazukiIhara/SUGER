#include "SwapChain.h"

#include <cassert>

void SwapChain::Initialize(DXGIManager* dxgi) {
	// DXGIのインスタンスをセット
	SetDXGI(dxgi);
}

UINT SwapChain::GetCurrentBuckBufferIndex() {
	return swapChain_->GetCurrentBackBufferIndex();
}

void SwapChain::SetDXGI(DXGIManager* dxgi) {
	assert(dxgi);
	dxgi_ = dxgi;
}
