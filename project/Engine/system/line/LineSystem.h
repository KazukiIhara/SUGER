#pragma once

// 前方宣言
class DirectXManager;
class GraphicsPipelineManager;

class LineSystem {
public:
	LineSystem() = default;
	~LineSystem() = default;

	// 初期化処理
	void Initialize(DirectXManager* directXManager, GraphicsPipelineManager* pipelineManager);

	// 描画前処理
	void PreDraw();
private:
	// DirectXCommon
	void SetDirectXManager(DirectXManager* directX) {
		directXManager_ = directX;
	}
	// PipelineManager
	void SetPipelineManager(GraphicsPipelineManager* pipelineManager) {
		pipelineManager_ = pipelineManager;
	}
private: // インスタンスを受け取るポインタ
	// DirectXManager
	DirectXManager* directXManager_ = nullptr;
	// PipelineManager
	GraphicsPipelineManager* pipelineManager_ = nullptr;

};