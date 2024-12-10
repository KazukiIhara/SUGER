#pragma once

// C++
#include <cmath>
#include <cassert>
#include <memory>

// DirectX
#include <d3d12.h>
#include <dxgi1_6.h>

// 自作ファイル
#include "directX/includes/ComPtr.h"

class DXGIManager;
class DirectXCommand;
class WindowManager;

class SwapChain {
public:
	SwapChain() = default;
	~SwapChain() = default;

	// 初期化
	void Initialize(WindowManager* windowmanager, DXGIManager* dxgi);

	// 現在のバックバッファインデックスを取得
	UINT GetCurrentBuckBufferIndex();

private:
	// スワップチェーン作成
	void CreateSwapChain();
	// DXGIをセット
	void SetDXGI(DXGIManager* dxgi);
	// WindowManagerをセット
	void SetWindowManager(WindowManager* windowManager);
private:
	// スワップチェーン
	ComPtr<IDXGISwapChain4> swapChain_ = nullptr;
	// スワップチェーンリソース
	ComPtr<ID3D12Resource> swapChainResources_[2] = { nullptr };
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc_{};
	// RTVリソースのインデックス
	uint32_t swapchainIndex_[2]{};
	// エラー判別君
	HRESULT hr_ = S_FALSE;
private:
	// dxgiのインスタンスを受け取る箱
	DXGIManager* dxgi_ = nullptr; 
	// WindowManagerのインスタンスを受け取る箱
	WindowManager* windowManager_ = nullptr;
};