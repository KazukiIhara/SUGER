#pragma once

class Fence {
public:
	Fence() = default;
	~Fence() = default;

	// 初期化
	void Initialize();

	void CreateFence();

private:
	// フェンス
	ComPtr<ID3D12Fence> fence_ = nullptr;
	// フェンスバリュー
	UINT64 fenceValue_ = 0;

};