#pragma once

// C++
#include <cstdint>

// DirectX
#include <d3d12.h>

#include "directX/includes/ComPtr.h"

// 前方宣言
class DirectXManager;
class DXGIManager;
class DirectXCommand;

class SRVManager {
public: // インスタンスコピー関数


public: // 公開メンバ関数
	SRVManager() = default;
	~SRVManager() = default;

	// 初期化
	void Initialize(DirectXManager* directX);
	// 割り当て関数
	uint32_t Allocate();
	// CPUの特定のインデックスハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE GetDescriptorHandleCPU(uint32_t index);
	// GPUの特定のインデックスハンドルを取得
	D3D12_GPU_DESCRIPTOR_HANDLE GetDescriptorHandleGPU(uint32_t index);
	// SRV生成(テクスチャ用)
	void CreateSrvTexture2d(uint32_t srvIndex, ID3D12Resource* pResource, DXGI_FORMAT format, UINT MipLevels);
	// SRV生成(StructuredBuffer用)
	void CreateSrvStructuredBuffer(uint32_t srvIndex, ID3D12Resource* pResource, uint32_t numElements, UINT structureByteStride);
	// Srvの数が最大数を上回っているかどうか
	bool IsLowerSrvMax();
	// 描画前処理
	void PreDraw();
	// ルートパラメータインデックスと、srv番号に対応したDescriptorTableを取得
	void SetGraphicsRootDescriptorTable(UINT rootParameterIndex, uint32_t srvIndex);

	// srvディスクリプタヒープを取得
	ID3D12DescriptorHeap* GetDescriptorHeap() const;

	// srvディスクリプタのサイズを取得
	uint32_t GetDescriptorSize() const;

private:
	// DirectX
	void SetDirectXManager(DirectXManager* directX);
public: // 公開メンバ変数
	// 最大SRV数
	static const uint32_t kMaxSRVCount = 512;
private: // 非公開メンバ変数
	// DescriptorHeap
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap_ = nullptr;
	// Discriptorのサイズ
	uint32_t descriptorSize_ = 0u;
	// 使用しているSrvのインデックス
	uint32_t useIndex = 0;
private: // インスタンスコピーポインタ
	// DirectXManager
	DirectXManager* directX_ = nullptr;
};