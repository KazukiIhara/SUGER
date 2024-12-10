#pragma once

class SwapChain;

class RenderTarget {
public:
	RenderTarget() = default;
	~RenderTarget() = default;

private:
	// スワップチェーンのインスタンスを受け取る箱
	SwapChain* swapChain_ = nullptr;
};
