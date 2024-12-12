#pragma once

// C++
#include <cstdint>
#include <cassert>

// DirectX
#include <d3d12.h>

#include "directX/includes/ComPtr.h"

class DXGIManager;

class Fence {
public:
	Fence() = default;
	~Fence() = default;

	// 初期化
	void Initialize(DXGIManager* dxgi);
	// GPUを待機
	void WaitGPU();
private:
	// フェンス作成
	void CreateFence();
private:
	// DXGIのインスタンスをセット
	void SetDXGI(DXGIManager* dxgi);
private:
	// フェンス
	ComPtr<ID3D12Fence> fence_ = nullptr;
	// フェンスバリュー
	UINT64 fenceValue_ = 0;
	// エラー判別君
	HRESULT hr_ = S_FALSE;
private:
	// DXGIのインスタンスを受け取る箱
	DXGIManager* dxgi_ = nullptr;
};