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

class SwapChain {
public:
	SwapChain() = default;
	~SwapChain() = default;

	// 初期化
	void Initialize(DXGIManager* dxgi);

	// 現在のバックバッファインデックスを取得
	UINT GetCurrentBuckBufferIndex();

private:
	// セットをDXGI
	void SetDXGI(DXGIManager* dxgi);

private:

	// スワップチェーン
	ComPtr<IDXGISwapChain4> swapChain_ = nullptr;

	// スワップチェーンリソース
	ComPtr<ID3D12Resource> swapChainResources_[2] = { nullptr };
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc_{};
	// RTVリソースのインデックス
	uint32_t swapchainIndex_[2]{};

private:
	// dxgiのインスタンスを受け取る箱
	DXGIManager* dxgi_ = nullptr;
};