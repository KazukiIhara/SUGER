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
class RTVManager;
class SRVUAVManager;

class RenderTexture {
public:
	RenderTexture() = default;
	~RenderTexture() = default;

	// 初期化
	void Initialize(DXGIManager* dxgi, DirectXCommand* command, RTVManager* rtvManager, SRVUAVManager* srvUavManager);

private:
	// DXGIをセット
	void SetDXGI(DXGIManager* dxgi);
	// Commandをセット
	void SetCommand(DirectXCommand* command);
	// RTVManagerのセット
	void SetRTVManager(RTVManager* rtvManager);
	// SRVUAVManagerのセット
	void SetSRVUAVManager(SRVUAVManager* srvUavManager);
private:
	// レンダーテクスチャ用のリソース
	ComPtr<ID3D12Resource> renderTextureResource = nullptr;
	// RTVリソースのインデックス
	uint32_t rtvIndex_ = 0;
private:
	// dxgiのインスタンスを受け取る箱
	DXGIManager* dxgi_ = nullptr;
	// Commandのインスタンスを受け取る箱
	DirectXCommand* command_ = nullptr;
	// RTVmanagerのインスタンスを受け取る箱
	RTVManager* rtvManager_ = nullptr;
	// SRVUAVManagerのインスタンスを受け取る箱
	SRVUAVManager* srvUavManager_ = nullptr;
};