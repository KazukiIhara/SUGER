#pragma once

// C++
#include <memory>

// DirectX
#include <d3d12.h>
#include <dxgi1_6.h>
#include <dxgidebug.h>
#include <dxcapi.h>

// 自作ファイル
#include "ComPtr.h"
#include "DXGIManager.h"

class DirectXCommand {
public:
	DirectXCommand() = default;
	~DirectXCommand() = default;

	void Initialize();

private:
	// SUCCEEDEDでエラー判別君
	HRESULT hr_ = S_FALSE;

	// DXGI
	std::unique_ptr<DXGIManager> dxgi_;

	// コマンドキュー
	ComPtr<ID3D12CommandQueue> commandQueue_ = nullptr;
	// コマンドアロケータ
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator_ = nullptr;
	// コマンドリスト
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList_ = nullptr;

};