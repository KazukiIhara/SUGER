#pragma once

#include <d3d12.h>

class DirectXCommand;
class SwapChain;
class RenderTexture;

class Barrier {
public:
	Barrier() = default;
	~Barrier() = default;

	// 初期化
	void Initialize(DirectXCommand* command, SwapChain* swapChain, RenderTexture* renderTexture);

	// スワップチェーン描画前のスワップチェーンのバリア
	void PreDrawBarrierSwapChain();
	// スワップチェーン描画後のスワップチェーンのバリア
	void PostDrawBarrierSwapChain();


private:
	// コマンドのインスタンスをセット
	void SetCommand(DirectXCommand* command);
	// スワップチェーンのインスタンスをセット
	void SetSwapChain(SwapChain* swapChain);
	// レンダーテクスチャのインスタンスをセット
	void SetRenderTexture(RenderTexture* renderTexture);

private:
	// リソースバリア
	D3D12_RESOURCE_BARRIER swapChainBarrier_{};
private:
	// コマンドのインスタンスを受け取る箱
	DirectXCommand* command_ = nullptr;
	// スワップチェーンのインスタンスを受け取る箱
	SwapChain* swapChian_ = nullptr;
	// レンダーテクスチャのインスタンスを受け取る箱
	RenderTexture* renderTexture_ = nullptr;
};