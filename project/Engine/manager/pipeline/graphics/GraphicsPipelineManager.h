#pragma once

// C++
#include <string>
#include <memory>

// DirectX
#include <d3d12.h>
#include <dxcapi.h>

// MyHedder
#include "directX/includes/ComPtr.h"
#include "enum/GraphicsPipelineEnum.h"

#include "2d/graphicsPipeline/Object2dGraphicsPipeline.h"
#include "3d/graphicsPipeline/Object3dGraphicsPipeline.h"

class DirectXManager;

class GraphicsPipelineManager {
public: // 公開メンバ変数
	GraphicsPipelineManager() = default;
	~GraphicsPipelineManager() = default;

	// 初期化
	void Initialize(DirectXManager* directXManager);

	// ルートシグネイチャのゲッター
	ID3D12RootSignature* GetRootSignature(PipelineState pipelineState);

	// パイプラインステイトのゲッター
	ID3D12PipelineState* GetPipelineState(PipelineState pipelineState, BlendMode blendMode);

	void SetRootSignature(PipelineState pipelineState);

	void SetGraphicsPipelineState(PipelineState pipelineState);

private: // 静的メンバ変数
	// ブレンドモードの数
	static const uint32_t kBlendModeNum = 6;
	// パイプラインの種類の数 
	static const uint32_t kGraphicsPipelineStateNum = 2;

private: // メンバ変数
	// ルートシグネイチャ
	ComPtr<ID3D12RootSignature> rootSignatures_[kGraphicsPipelineStateNum];
	// グラフィックスパイプライン
	ComPtr<ID3D12PipelineState> graphicsPipelineStates_[kGraphicsPipelineStateNum][kBlendModeNum];

private: // インスタンスを受け取るポインタ
	// 2DGraphicsPipelineManager
	std::unique_ptr<Object2DGraphicsPipeline> object2dGraphicsPipeline_ = nullptr;
	// 3DGraphicsPipelineManager
	std::unique_ptr<Object3DGraphicsPipeline> object3dGraphicsPipeline_ = nullptr;
};
