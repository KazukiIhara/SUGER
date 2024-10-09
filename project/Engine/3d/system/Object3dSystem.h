#pragma once

#pragma once

// 前方宣言
class DirectXManager;
class GraphicsPipelineManager;

class cObject3dSystem {
public: // インスタンスセット関数
	// DirectXCommon
	void SetDirectXCommon(DirectXManager* directX) {
		directX_ = directX;
	}
	// PipelineManager
	void SetPipelineManager(GraphicsPipelineManager* pipelineManager) {
		pipelineManager_ = pipelineManager;
	}

public: // 公開メンバ関数
	cObject3dSystem() = default;
	~cObject3dSystem() = default;

	// 描画前処理
	void PreDraw();

private: // インスタンスを受け取るポインタ
	// DirectXManager
	DirectXManager* directXManager_ = nullptr;
	// PipelineManager
	GraphicsPipelineManager* pipelineManager_ = nullptr;

};