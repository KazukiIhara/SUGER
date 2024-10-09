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

	void SetGraphicsPipeline(PipelineState pipelineState);

private: // 静的メンバ変数
	// ブレンドモードの数
	static const uint32_t kBlendModeNum = 6;
	// パイプラインの種類の数 
	static const uint32_t kPipelineStateNum = 1;

private: // メンバ変数
	// ルートシグネイチャ
	ComPtr<ID3D12RootSignature> rootSignatures_[kPipelineStateNum];
	// グラフィックスパイプライン
	ComPtr<ID3D12PipelineState> graphicsPipelineStates_[kPipelineStateNum][kBlendModeNum];

private: // インスタンスを受け取るポインタ
	// 2DGraphicsPipelineManager
	std::unique_ptr<Object2DGraphicsPipeline> object2dGraphicsPipeline_ = nullptr;

};
