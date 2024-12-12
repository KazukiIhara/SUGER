#pragma once

#include "math/types/Vector4.h"

class DirectXCommand;
class SwapChain;
class DepthStencil;

class TargetRenderPass {
public:
	TargetRenderPass() = default;
	~TargetRenderPass() = default;

	// 初期化
	void Initialize(DirectXCommand* command, SwapChain* swapChain, DepthStencil* depthStencil);
	// レンダーターゲットのセット
	void SetRenderTarget();
	// レンダーターゲットのクリア
	void ClearRenderTarget();

	// クリアカラーのセット
	void SetClearColor(const Vector4& clearColor);
private:
	// コマンドのインスタンスをセット
	void SetCommand(DirectXCommand* command);
	// スワップチェーンのインスタンスをセット
	void SetSwapChain(SwapChain* swapChain);
	// デプスステンシルをセット
	void SetDepthStencil(DepthStencil* depthStencil);
private:
	// コマンドのインスタンスを受け取る箱
	DirectXCommand* command_ = nullptr;
	// スワップチェーンのインスタンスを受け取る箱
	SwapChain* swapChain_ = nullptr;
	// デプスステンシルのインスタンスを受け取る箱
	DepthStencil* depthStencil_ = nullptr;
	// 画面クリアカラー
	Vector4 clearColor_ = { 0.05f,0.05f,0.05f,1.0f };

};
