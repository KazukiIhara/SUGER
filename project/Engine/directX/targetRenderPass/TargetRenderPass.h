#pragma once


class DirectXCommand;
class SwapChain;

class TargetRenderPass {
public:
	TargetRenderPass() = default;
	~TargetRenderPass() = default;

	// 初期化
	void Initialize(DirectXCommand* command, SwapChain* swapChain);
	// レンダーターゲットのセット
	void SetRenderTarget();
	// レンダーターゲットのクリア
	void ClearRenderTarget();
private:
	// コマンドのインスタンスをセット
	void SetCommand(DirectXCommand* command);
	// スワップチェーンのインスタンスをセット
	void SetSwapChain(SwapChain* swapChain);

private:
	// コマンドのインスタンスを受け取る箱
	DirectXCommand* command_ = nullptr;
	// スワップチェーンのインスタンスを受け取る箱
	SwapChain* swapChain_ = nullptr;
};
