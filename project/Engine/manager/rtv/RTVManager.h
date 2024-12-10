#pragma once

// C++
#include <cstdint>

// DirectX
#include <d3d12.h>

#include "directX/includes/ComPtr.h"

// 前方宣言
class DXGIManager;

class RTVManager {
public:
	RTVManager() = default;
	~RTVManager() = default;

	// 初期化
	void Initialize(DXGIManager* dxgi);

private:
	// DXGIManagerのセット
	void SetDXGI(DXGIManager* dxgi);
public:
	// 最大RTV数
	static const uint32_t kMaxViewCount = 512;
private:
	// DescriptorHeap
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap_ = nullptr;
	// Discriptorのサイズ
	uint32_t descriptorSize_ = 0u;
	// 使用しているviewのインデックス
	uint32_t useIndex = 0;
private:
	// dxgiのインスタンス
	DXGIManager* dxgi_ = nullptr;
};