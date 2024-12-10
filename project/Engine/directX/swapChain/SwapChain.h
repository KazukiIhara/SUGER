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
class RTVManager;

class SwapChain {
public:
	SwapChain() = default;
	~SwapChain() = default;

	// 初期化
	void Initialize(WindowManager* windowmanager, DXGIManager* dxgi, DirectXCommand* command, RTVManager* rtvManager);

	// 現在のバックバッファインデックスを取得
	UINT GetCurrentBuckBufferIndex();

private:
	// スワップチェーン作成
	void CreateSwapChain();
	// スワップチェーンのRTVリソースを作成
	void CreateSwapChainResources();
private:
	// WindowManagerをセット
	void SetWindowManager(WindowManager* windowManager);
	// DXGIをセット
	void SetDXGI(DXGIManager* dxgi);
	// Commandをセット
	void SetCommand(DirectXCommand* command);
	// RTVManagerのセット
	void SetRTVManager(RTVManager* rtvManager);
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
	// WindowManagerのインスタンスを受け取る箱
	WindowManager* windowManager_ = nullptr;
	// dxgiのインスタンスを受け取る箱
	DXGIManager* dxgi_ = nullptr;
	// Commandのインスタンスを受け取る箱
	DirectXCommand* command_ = nullptr;
	// RTVmanagerのインスタンスを受け取る箱
	RTVManager* rtvManager_ = nullptr;
};