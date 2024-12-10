#include "SwapChain.h"

#include <cassert>

#include "directX/dxgi/DXGIManager.h"
#include "manager/window/WindowManager.h"

void SwapChain::Initialize(WindowManager* windowmanager, DXGIManager* dxgi) {
	// WindowManagerのインスタンスをセット
	SetWindowManager(windowmanager);
	// DXGIのインスタンスをセット
	SetDXGI(dxgi);
	// スワップチェーン作成
	CreateSwapChain();
}

UINT SwapChain::GetCurrentBuckBufferIndex() {
	return swapChain_->GetCurrentBackBufferIndex();
}

void SwapChain::CreateSwapChain() {
	// スワップチェーンの設定
	swapChainDesc_.Width = WindowManager::kClientWidth;				// 画面の幅、ウィンドウのクライアント領域を同じものにしておく
	swapChainDesc_.Height = WindowManager::kClientHeight;				// 画面の高さ、ウィンドウのクライアント領域を同じものしておく
	swapChainDesc_.Format = DXGI_FORMAT_R8G8B8A8_UNORM;			// 色形式
	swapChainDesc_.SampleDesc.Count = 1;						// マルチサンプルしない
	swapChainDesc_.BufferCount = 2;								// ダブルバッファ
	swapChainDesc_.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;	// モニタにうつしたら、中身を破棄
	// コマンドキュー、ウィンドウハンドル、設定を渡して生成する
	hr_ = dxgi_->GetFactory()->CreateSwapChainForHwnd(commandQueue_.Get(), windowManager_->GetHwnd(), &swapChainDesc_,
		nullptr, nullptr, reinterpret_cast<IDXGISwapChain1**>(swapChain_.GetAddressOf()));
	assert(SUCCEEDED(hr_));
}

void SwapChain::SetDXGI(DXGIManager* dxgi) {
	assert(dxgi);
	dxgi_ = dxgi;
}

void SwapChain::SetWindowManager(WindowManager* windowManager) {
	assert(windowManager);
	windowManager_ = windowManager;
}
