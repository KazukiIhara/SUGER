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

	void Initialize(DXGIManager* dxgi);

	ID3D12CommandQueue* GetQueue();
	ID3D12CommandAllocator* GetAllocator();
	ID3D12GraphicsCommandList* GetList();

	void SetDXGIManager(DXGIManager* dxgi);
private:
	// SUCCEEDEDでエラー判別君
	HRESULT hr_ = S_FALSE;

	// DXGI
	DXGIManager* dxgi_ = nullptr;

	// コマンドキュー
	ComPtr<ID3D12CommandQueue> commandQueue_ = nullptr;
	// コマンドアロケータ
	ComPtr<ID3D12CommandAllocator> commandAllocator_ = nullptr;
	// コマンドリスト
	ComPtr<ID3D12GraphicsCommandList> commandList_ = nullptr;

};