#pragma once
#include "directX/includes/ComPtr.h"

// DirectX
#include <d3d12.h>
#include <dxgi1_6.h>

class DXGIManager {
public:
	DXGIManager() = default;
	~DXGIManager() = default;

	void Initialize();

	ID3D12Device* GetDevice();
	IDXGIFactory7* GetFactory();
private:
	// エラー判別
	HRESULT hr_ = S_FALSE;
	// DXGIファクトリー
	ComPtr <IDXGIFactory7> dxgiFactory_ = nullptr;
	// 使用するアダプタ用の変数
	ComPtr<IDXGIAdapter4> useAdapter_ = nullptr;
	// Device
	ComPtr<ID3D12Device> device_ = nullptr;
};