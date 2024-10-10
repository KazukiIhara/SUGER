#pragma once

#pragma once

// 前方宣言
class DirectXManager;
class GraphicsPipelineManager;

class Object3DSystem {
public: // 公開メンバ関数
	Object3DSystem() = default;
	~Object3DSystem() = default;

	// 初期化処理
	void Initialize(DirectXManager* directXManager, GraphicsPipelineManager* pipelineManager_);

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