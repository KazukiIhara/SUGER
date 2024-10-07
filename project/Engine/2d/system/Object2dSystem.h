#pragma once

// 前方宣言
class DirectXManager;
class GraphicsPipelineManager;

class Object2DSystem {
public: // 公開メンバ変数
	Object2DSystem() = default;
	~Object2DSystem() = default;

	// 初期化
	void Initialize(DirectXManager* directX, GraphicsPipelineManager* pipelineManager);

	// 描画前処理
	void PreDraw();
private:
	// DirectXCommon
	void SetDirectXManager(DirectXManager* directX) {
		directX_ = directX;
	}
	// PipelineManager
	void SetPipelineManager(GraphicsPipelineManager* pipelineManager) {
		pipelineManager_ = pipelineManager;
	}
private: // インスタンスを受け取るポインタ
	// DirectXCommon
	DirectXManager* directX_ = nullptr;
	// PipelineManager
	GraphicsPipelineManager* pipelineManager_ = nullptr;

};