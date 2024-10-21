#pragma once

// C++
#include <chrono>
#include <cmath>
#include <cassert>
#include <memory>

// DirectX
#include <d3d12.h>
#include <dxgi1_6.h>
#include <dxgidebug.h>
#include <dxcapi.h>

// 自作ファイル
#include "directX/includes/ComPtr.h"
#include "manager/dxgi/DXGIManager.h"
#include "directX/command/DirectXCommand.h"

// 前方宣言
class WindowManager;

// DirectX基本処理クラス
class DirectXManager {
public: // 公開メンバ関数
	DirectXManager() = default;
	~DirectXManager() = default;

	// 初期化
	void Initialize(WindowManager* windowManager, bool enableDebugLayer = true);
	// 描画前処理
	void PreDraw();
	// 描画後処理
	void PostDraw();

	// コマンドの実行
	void KickCommand();

	// GPUを待機
	void WaitGPU();

	// コマンドリストをリセット
	void ResetCommandList();

	// スワップチェインディスクリプタを取得
	DXGI_SWAP_CHAIN_DESC1 GetSwapChainDesc() const {
		return swapChainDesc_;
	}
	// rtvDescを取得
	D3D12_RENDER_TARGET_VIEW_DESC GetRTVDesc() const {
		return rtvDesc_;
	}

	ID3D12Device* GetDevice();

	ID3D12CommandQueue* GetCommandQueue();
	ID3D12CommandAllocator* GetCommandAllocator();
	ID3D12GraphicsCommandList* GetCommandList();

	// CPUの特定のインデックスのハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE GetCPUDescriptorHandle(ID3D12DescriptorHeap* descriptorHeap, uint32_t descriptorSize, uint32_t index);
	// GPUの特定のインデックスのハンドルを取得
	D3D12_GPU_DESCRIPTOR_HANDLE GetGPUDescriptorHandle(ID3D12DescriptorHeap* descriptorHeap, uint32_t descriptorSize, uint32_t index);

	// バッファリソースの作成
	Microsoft::WRL::ComPtr<ID3D12Resource> CreateBufferResource(size_t sizeInBytes);

	// ディスクリプタヒープの作成
	static Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> CreateDescriptorHeap(ID3D12Device* device, D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible);

private: // プライベートメンバ関数

	// WinAPIのインスタンスをコピー
	void SetWindowManager(WindowManager* windowManager) {
		windowManager_ = windowManager;
	}

	// スワップチェーンを生成する
	void CreateSwapChain();

	// レンダーターゲットビューを生成する
	void CreateRenderTargetView();

	// デプスステンシルビューを生成する
	void CreateDepthStencilView();

	// フェンスを生成する
	void CreateFence();

	// 深度クリア
	void ClearDepthView();
	// レンダーターゲットのクリア
	void ClearRenderTarget(float clearColor[]);
	// レンダーターゲットのセット
	void SetRenderTargets();

	// ビューポートの設定
	void SettingViewport();

	// シザー矩形の設定
	void SettingScissorRect();

	// FPS固定処理

	// FPS固定処理初期化
	void InitializeFixFPS();
	// FPS固定処理更新
	void UpdateFixFPS();

	// デプスステンシルリソースの作成
	Microsoft::WRL::ComPtr<ID3D12Resource> CreateDepthStencilTextureResource(ID3D12Device* device, int32_t width, int32_t height);

private: // メンバ変数

	// DXGI
	std::unique_ptr<DXGIManager> dxgi_;
	// DirectXCommand
	std::unique_ptr<DirectXCommand> dxCommand_;

	// SUCCEEDEDでエラー判別君
	HRESULT hr_ = S_FALSE;


	// スワップチェーン
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc_{};
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain_ = nullptr;

	// DepthStencilResource
	Microsoft::WRL::ComPtr<ID3D12Resource> depthStencilResource_ = nullptr;

	// ディスクリプタヒープ
	// DSV用
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> dsvDescriptorHeap_ = nullptr;
	// RTV用
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvDescriptorHeap_ = nullptr;
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc_{};

	// スワップチェーンリソース
	Microsoft::WRL::ComPtr<ID3D12Resource> swapChainResources_[2] = { nullptr };

	// フェンス
	Microsoft::WRL::ComPtr<ID3D12Fence> fence_ = nullptr;

	// RTVを2つ作るのでディスクリプタを2つ用意
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandles_[2] = { 0 };

	// DSVのディスクリプタ
	D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle_;

	// バリア
	D3D12_RESOURCE_BARRIER barrier_{};

	// バックバッファインデックス
	UINT backBufferIndex_ = 0;

	// フェンスバリュー
	UINT64 fenceValue_ = 0;

	// 記録時間(FPS固定用)
	std::chrono::steady_clock::time_point reference_;

	// DescriptorSize取得
	uint32_t descriptorSizeRTV_ = 0u;
	uint32_t descriptorSizeDSV_ = 0u;

	// 目標FPS
	double targetFPS_ = 60.0;

private: // インスタンスコピーポインタ
	WindowManager* windowManager_ = nullptr;
};