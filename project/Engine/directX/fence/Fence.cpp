#include "Fence.h"


#include "directX/dxgi/DXGIManager.h"

void Fence::Initialize() {
	// フェンスバリューを0
	fenceValue_ = 0;
	// フェンスの作成
	CreateFence();
}

void Fence::CreateFence() {
	// 初期値0でフェンスを作る
	hr_ = dxgi_->GetDevice()->CreateFence(fenceValue_, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence_));
	assert(SUCCEEDED(hr_));
}

void Fence::SetDXGI(DXGIManager* dxgi) {
	assert(dxgi);
	dxgi_ = dxgi;
}
